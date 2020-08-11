/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_unnecessary_tubes.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 16:34:23 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/01 16:34:23 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void		setup_diamond(t_diamond *curr, t_connection *side_nb,
t_connection *src_side, t_connection *nb_src)
{
	curr->common_dst_found = 0;
	curr->nb_src = nb_src;
	curr->src_side = src_side;
	curr->side_nb = side_nb;
	curr->curr_nb_nb = NULL;
	curr->curr_nb_side = NULL;
	curr->nb_improved_by_side = 0;
	curr->side_improved_by_nb = 0;
	setup_conn(&curr->nb_dst, side_nb->src);
	setup_conn(&curr->side_dst, nb_src->src);
}

static void	compr_side_dst(t_diamond *curr, t_map *map)
{
	if (DEBUG == 1)
		printf("Compare side and nb dst\n");
	set_conn(&(curr->nb_dst), curr->curr_nb_nb);
	if (curr->nb_dst.dst->is_junction == 0)
		find_real_nb(&curr->nb_dst, map);
	if (DEBUG == 1)
	{
		printf("nb to dst\n");
		print_connection(&curr->nb_dst);
		printf("side to dst\n");
		print_connection(&curr->side_dst);
	}
	if (curr->side_dst.dst == curr->nb_dst.dst)
	{
		curr->common_dst_found = 1;
		if (DEBUG == 1)
		{
			printf("\n\ntotal len side %lu\ntotal len nb %lu\nSide through nb %lu\nNb through side %lu\nside to dst %lu\nnb to dst %lu\n\n",
			(curr->src_side->dist + curr->side_dst.dist), (curr->nb_src->dist + curr->nb_dst.dist),
			(curr->src_side->dist + curr->nb_dst.dist), (curr->nb_src->dist + curr->side_dst.dist),
			curr->side_dst.dist, curr->nb_dst.dist);
		}
		if ((curr->side_dst.dist + curr->side_nb->dist) < curr->nb_dst.dist)
			curr->nb_improved_by_side++;
		if ((curr->nb_dst.dist + curr->side_nb->dist) < curr->side_dst.dist)
				curr->side_improved_by_nb++;
	}
	if (DEBUG == 1)
		printf("nb improved by side: %lu\nside improved by nb: %lu\n", curr->nb_improved_by_side, curr->side_improved_by_nb);
}

static void	compr_nb_side_dst(t_diamond *curr, t_map *map)
{
	size_t	j;

	if (DEBUG == 1)
		printf("Compare nb through side dst\n");
	set_conn(&curr->side_dst, curr->curr_nb_side);
	if (curr->side_dst.dst->is_junction == 0)
		find_real_nb(&curr->side_dst, map);
	j = 0;
	while (j < curr->nb_src->src->neighbours_len)
	{
		setup_conn(&curr->nb_dst, curr->nb_src->src);
		if (curr->nb_src->src->neighbours[j] != NULL
			&& check_dst_src(curr->side_nb, curr->nb_src,
			curr->nb_src->src->neighbours[j]) == 0)
		{
			curr->curr_nb_nb = curr->nb_src->src->neighbours[j];
			compr_side_dst(curr, map);
		}
		j++;
	}	
}

int		has_conn_to(t_room *curr, t_room *nb)
{
	size_t	i;

	i = 0;
	while (i < curr->neighbours_len)
	{
		if (curr->neighbours[i] == nb)
			return (1);
		i++;
	}
	return (0);
}

int		rm_un_conn(t_connection *side_nb,
t_connection *src_side, t_connection *nb_src, t_map *map)
{
	t_diamond		curr;
	size_t			i;
	int				changed;

	i = 0;
	changed = 0;
	if (DEBUG == 1)
		printf("\n\nRM UN CONN\n");
	setup_diamond(&curr, side_nb, src_side, nb_src);
	if (DEBUG == 1)
	{
		print_connection(&curr.side_dst);
		print_connection(&curr.nb_dst);
	}
	while (i < side_nb->src->neighbours_len)
	{
		setup_conn(&curr.side_dst, side_nb->src);
		if (side_nb->src->neighbours[i] != NULL
		&& check_dst_src(src_side, side_nb, side_nb->src->neighbours[i])
		== 0)
		{
			if (DEBUG == 1)
				printf("Valid nb found\n");
			curr.curr_nb_side = side_nb->src->neighbours[i];
			compr_nb_side_dst(&curr, map);
		}
		i++;
	}
	if (DEBUG == 1)
	{
		printf("After looking for dsts\n");
		printf("Connection nb to dst\n");
		print_connection(&curr.nb_dst);
		printf("Connection side to dst\n");
		print_connection(&curr.side_dst);
		printf("side improved by nb %lu\nnb improved by side %lu\n",
		curr.side_improved_by_nb, curr.nb_improved_by_side);
	}
	if (curr.common_dst_found == 1)
	{
		if (curr.nb_improved_by_side == 0
		&& (curr.src_side->dst != map->end && curr.src_side->dst != map->start)
		&& has_conn_to(side_nb->dst, side_nb->dst_nb) == 1)
		{
			if (DEBUG == 1)
				printf("Going through side is not better\n");
			changed = 1;
			del_tube(side_nb->dst, side_nb->dst_nb, map);
			if (side_nb->dist != 1)
				del_tube(side_nb->dst_nb, side_nb->dst, map);
		}
		if (curr.side_improved_by_nb == 0
		&& (curr.nb_dst.src != map->end && curr.nb_dst.src != map->start)
		&& has_conn_to(side_nb->src, side_nb->src_nb) == 1)
		{
			changed = 1;
			if (DEBUG == 1)
				printf("Going through nb is not better\n");
			del_tube(side_nb->src, side_nb->src_nb, map);
			if (side_nb->dist != 1)
				del_tube(side_nb->src_nb, side_nb->src, map);
		}
	}
	if (curr.common_dst_found == 0)
	{
		if (DEBUG == 1)
			printf("No common dst\n");
	}
	return (changed);
}

ssize_t			setup_q_un(t_conn_wrap **qr, t_map *map)
{
	(*qr) = (t_conn_wrap *)malloc(sizeof(t_conn_wrap));
	if (*qr)
	{
		(*qr)->q = (t_connection **)malloc(sizeof(t_connection *));
		if ((*qr)->q)
		{
			*(*qr)->q = NULL;
			if (bite_alloc(&(*qr)->visited, map) == EXIT_SUCCESS)
			{
				(*qr)->items = 0;
				return (EXIT_SUCCESS);
			}
			free ((*qr)->q);
			(*qr)->q = NULL;
		}
		free (*qr);
		(*qr) = NULL;
	}
	return (EXIT_FAILURE);
}

static void			remove_duplicate_paths(t_connection **conn, t_map *map,
int *changed)
{
	t_connection	curr;
	t_connection	other;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	/* WE MIGHT REMOVE Q PATH */
	if (DEBUG == 1)
	{
		printf("REMOVE DUPL PATHS\n");
		for (size_t j=0; j < (*conn)->dst->neighbours_len; j++)
		{
			printf("nb %s ", (*conn)->dst->neighbours[j]->name);
			printf("\n\n");
		}
	}
	setup_conn(&curr, (*conn)->dst);
	while (i < (*conn)->dst->neighbours_len)
	{
		setup_conn(&curr, (*conn)->dst);
		if (DEBUG == 1)
			print_connection(&curr);
		if ((*conn)->dst->neighbours[i] != (*conn)->dst_nb
		&& (*conn)->dst->neighbours[i] != (*conn)->src_nb)
		{
			if (DEBUG == 1)
				printf("Candidate rm dupl paths %s\n", (*conn)->dst->neighbours[i]->name);
			set_conn(&curr, (*conn)->dst->neighbours[i]);
			// print_connection(&curr);
			// printf("Before find real nb\n");
			if (curr.dst->is_junction == 0)
				find_real_nb(&curr, map);
			// printf("After find real nb\n");
			if (curr.dst)
			{
				if (DEBUG == 1)
					printf("real nb %s\n", curr.dst->name);
			}
			if (curr.dst == NULL)
			{
				i -= handle_nowhere_to_go(curr.src, curr.src_nb, map);
				*changed = 1;
				if (DEBUG == 1)
					printf("Nowhere to go remove dupl paths curr\n");
					// exit (0);
			}
			else if (curr.dst == curr.src)
			{
				if (DEBUG == 1)
					printf("Loop\n");
				handle_loop(&curr, map, changed, &i);
			}
			else
			{
				if (DEBUG == 1)
					printf("Look for others\n");
				j = 0;
				while (j < (*conn)->dst->neighbours_len)
				{
					setup_conn(&other, (*conn)->dst);
					if ((*conn)->dst->neighbours[j] != NULL
					&& (*conn)->dst->neighbours[j] != (*conn)->dst_nb
					&& (*conn)->dst->neighbours[j] != (*conn)->src_nb
					&& j != i)
					{
						set_conn(&other, (*conn)->dst->neighbours[j]);
						// print_connection(&other);
						if (other.dst->is_junction == 0)
							find_real_nb(&other, map);
						// printf("After find real nb\n");
						if (other.dst == NULL)
						{
							if (DEBUG == 1)
								printf("Nowhere to go remove dupl paths other\n");
							j -= handle_nowhere_to_go(other.src, other.src_nb, map);
							*changed = 1;
								// exit (0);
						}
						else if (other.dst == other.src)
						{
							if (DEBUG == 1)
								printf("Loop\n");
							handle_loop(&other, map, changed, &j);
						}
						else if (curr.dst == other.dst)
						{
							if (DEBUG == 1)
							{
								printf("I: %lu J: %lu\n\n", i, j);
								printf("Curr\n");
								print_connection(&curr);
								printf("Other\n");
								print_connection(&other);
							}
							if (curr.dist < other.dist)
							{
								if (DEBUG == 1)
									printf("curr < other\n");
								*changed = 1;
								del_tube(other.src, other.src_nb, map);
								del_tube(other.src_nb, other.src, map);
								del_tube(other.dst, other.dst_nb, map);
								del_tube(other.dst_nb, other.dst, map);
								j--;
							}
							else
							{
								if (DEBUG == 1)
									printf("curr >= other\n");
								*changed = 1;
								del_tube(curr.src, curr.src_nb, map);
								del_tube(curr.src_nb, curr.src, map);
								del_tube(curr.dst, curr.dst_nb, map);
								del_tube(curr.dst_nb, curr.dst, map);
								curr = other;
								i = 0;
							}
						}
					}
					j++;
				}
			}
		}
		i++;
	}
}

ssize_t			execute_queue_un(t_conn_wrap *qr, t_map *map, int *changed)
{
	t_connection	*iter;
	t_connection	*prev;
	size_t			tmp;

	iter = *(qr->q);
	prev = NULL;
	tmp = 0;
	while (iter)
	{
		if (DEBUG == 1)
			printf("QUEUE ITEM dst %s %d src %s dist %lu\n", iter->dst->name, iter->dst->is_junction,
			iter->src->name, iter->dist);
		remove_duplicate_paths(&iter, map, changed);
		if (DEBUG == 1)
			printf("AFTER RM DUPL PATHS\n");
		if (iter->dst->is_junction == 0)
			find_real_nb(iter, map);
		if (DEBUG == 1)
			printf("QUEUE ITEM AFTER dst %s %d src %s dist %lu\n", iter->dst->name, iter->dst->is_junction,
		iter->src->name, iter->dist);
		// print_connection(iter);
		if (iter->dst == NULL)
		{
			if (DEBUG == 1)
				printf("Nowhere to go execute queue un\n");
			handle_nowhere_to_go(iter->src, iter->src_nb, map);
			// del_tube(iter->src, iter->src_nb, map);
			prev = iter;
			iter = iter->next;
			remove_q_item_un(qr, prev);
			*changed = 1;
		}
		else if (iter->dst == iter->src)
		{
			if (DEBUG == 1)
				printf("Handle loop execute queue\n");
			handle_loop(iter, map, changed, &tmp);
			prev = iter;
			iter = iter->next;
			remove_q_item_un(qr, prev);
			// *changed = 1;
		}
		else
		{
			if (!(iter->src == map->start && iter->dst == map->end))
			{
				/* If 0 is returned the curr iter has been deleted */
				if (DEBUG == 1)
					printf("Before del un_tubes\n");
				if (del_un_tubes(iter, changed, map) == 1)
				{
					if (DEBUG == 1)
						printf("\n\nAFTER DEL UN TUBES\n");
					iter = iter->next;
				}
				else
				{
					prev = iter;
					iter = iter->next;
					remove_q_item_un(qr, prev);
				}
			}
			else
				iter = iter->next;
		}
		if (iter == NULL)
		{
			if (DEBUG == 1)
				printf("Before update queue\n");
			if (update_queue_un(qr, map, changed) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			iter = *(qr->q);
		}
	}
	free (qr->visited);
	free (qr->q);
	free (qr);
	return (EXIT_SUCCESS);
}

ssize_t			remove_unnecessary_tubes(t_map *map, int *changed)
{
	t_conn_wrap		*qr;

	*changed = 0;
	if (setup_q_un(&qr, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (DEBUG == 1)
		print_connection_queue(qr->q);
	if (un_add_start_nbs_to_q(map->start, qr, map, changed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (execute_queue_un(qr, map, changed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
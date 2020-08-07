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
	set_conn(&(curr->nb_dst), curr->curr_nb_nb);
	if (curr->nb_dst.dst->is_junction == 0)
		find_real_nb(curr->nb_dst.src, &curr->nb_dst, map);
	if (curr->side_dst.dst == curr->nb_dst.dst)
	{
		if ((curr->src_side->dist + curr->side_dst.dist)
		< (curr->nb_src->dist + curr->nb_dst.dist))
		{
			if ((curr->side_dst.dist + curr->side_nb->dist) < curr->nb_dst.dist)
				curr->nb_improved_by_side++;
		}
		else if ((curr->nb_src->dist + curr->nb_dst.dist)
		< (curr->src_side->dist + curr->side_dst.dist))
		{
			if ((curr->nb_dst.dist + curr->side_nb->dist) < curr->side_dst.dist)
				curr->side_improved_by_nb++;
		}
	}
}

static void	compr_nb_side_dst(t_diamond *curr, t_map *map)
{
	size_t	j;

	set_conn(&curr->side_dst, curr->curr_nb_side);
	if (curr->side_dst.dst->is_junction == 0)
		find_real_nb(curr->side_dst.src, &curr->side_dst, map);
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
	setup_diamond(&curr, side_nb, src_side, nb_src);
	while (i < side_nb->src->neighbours_len)
	{
		setup_conn(&curr.side_dst, side_nb->src);
		if (side_nb->src->neighbours[i] != NULL
		&& check_dst_src(src_side, side_nb, side_nb->src->neighbours[i])
		== 0)
		{
			curr.curr_nb_side = side_nb->src->neighbours[i];
			compr_nb_side_dst(&curr, map);
		}
		i++;
	}
	// printf("Connection nb to dst\n");
	// print_connection(&nb_to_dst);
	// printf("Connection side to dst\n");
	// print_connection(&side_to_dst);
	// printf("side improved by nb %d\nnb improved by side %d\n",
	// side_improved_by_nb, nb_improved_by_side);
	if (curr.nb_improved_by_side == 0
	&& has_conn_to(side_nb->dst, side_nb->dst_nb) == 1)
	{
		// printf("Going through side is not better\n");
		changed = 1;
		del_tube(side_nb->dst, side_nb->dst_nb, map);
	}
	if (curr.side_improved_by_nb == 0
	&& has_conn_to(side_nb->src, side_nb->src_nb) == 1)
	{
		changed = 1;
		// printf("Going through nb is not better\n");
		del_tube(side_nb->src, side_nb->src_nb, map);
	}
	return (changed);
}

ssize_t			setup_q_un(t_conn_wrap **qr, t_map *map)
{
	(*qr) = (t_conn_wrap *)malloc(sizeof(t_conn_wrap));
	if (*qr)
	{
		if (create_q(((void ***)(&(*qr)->q)), sizeof(t_connection *))
		== EXIT_SUCCESS)
		{
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
	size_t			tmp;

	i = 0;
	j = 0;
	tmp = 0;
	setup_conn(&curr, (*conn)->dst);
	while (i < (*conn)->dst->neighbours_len)
	{
		setup_conn(&curr, (*conn)->dst);
		if ((*conn)->dst->neighbours[i] != NULL
		&& (*conn)->dst->neighbours[i] != (*conn)->dst_nb
		&& (*conn)->dst->neighbours[i] != (*conn)->src_nb)
		{
			set_conn(&curr, (*conn)->dst->neighbours[i]);
			if (curr.dst->is_junction == 0)
				find_real_nb(curr.src, &curr, map);
			if (curr.dst == NULL)
				printf("Nowhere to go\n");
			else if (curr.dst == curr.src)
			{
				printf("Loop\n");
				handle_loop(&curr, map, changed, &tmp);
			}
			else
			{
				j = i + 1;
				while (j < (*conn)->dst->neighbours_len)
				{
					setup_conn(&other, (*conn)->dst);
					if ((*conn)->dst->neighbours[j] != NULL
					&& (*conn)->dst->neighbours[j] != (*conn)->dst_nb
					&& (*conn)->dst->neighbours[j] != (*conn)->src_nb)
					{
						set_conn(&other, (*conn)->dst->neighbours[j]);
						if (other.dst->is_junction == 0)
							find_real_nb(other.src, &other, map);
						if (other.dst == NULL)
							printf("Nowhere to go\n");
						else if (other.dst == other.src)
							handle_loop(&other, map, changed, &tmp);
						else if (curr.dst == other.dst)
						{
							// printf("Curr\n");
							// print_connection(&curr);
							// printf("Other\n");
							// print_connection(&other);
							if (curr.dist < other.dist)
							{
								// printf("curr < other\n");
								*changed = 1;
								del_tube(other.src, other.src_nb, map);
								del_tube(other.dst, other.dst_nb, map);
								j--;
							}
							else
							{
								// printf("curr >= other\n");
								*changed = 1;
								del_tube(curr.src, curr.src_nb, map);
								del_tube(curr.dst, curr.dst_nb, map);
								curr = other;
								i = j - 2;
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
		printf("QUEUE ITEM dst %s %d src %s dist %lu\n", iter->dst->name, iter->dst->is_junction,
		iter->src->name, iter->dist);
		remove_duplicate_paths(&iter, map, changed);
		if (iter->dst->is_junction == 0)
			find_real_nb(iter->dst, iter, map);
		if (iter->dst == NULL)
		{
			del_tube(iter->src, iter->src_nb, map);
			prev = iter;
			iter = iter->next;
			remove_q_item_un(qr, prev);
			*changed = 1;
		}
		else if (iter->dst == iter->src)
		{
			handle_loop(iter, map, changed, &tmp);
			prev = iter;
			iter = iter->next;
			remove_q_item_un(qr, prev);
			*changed = 1;
		}
		else
		{
			if (!(iter->src == map->start && iter->dst == map->end))
			{
				/* If 0 is returned the curr iter has been deleted */
				if (del_un_tubes(qr, iter, changed, map) == 1)
					iter = iter->next;
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
			update_queue_un(qr, map, changed);
			iter = *(qr->q);
		}
	}
	free (qr->visited);
	free (qr->q);
	free (qr);
}

void			remove_sps_spe_conns(t_map *map, int *changed)
{
	size_t	i;
	size_t	j;
	t_room	*tmp;

	i = 0;
	j = 0;
	while (i < map->rooms->size)
	{
		if (((t_entry *)map->rooms->entries[i]) != NULL)
		{
			tmp = ((t_room *)map->rooms->entries[i]->val);
			if (tmp->sps == 1 && tmp != map->start)
			{
				j = 0;
				while (j < tmp->neighbours_len)
				{
					if (tmp->neighbours[j] != NULL
					&& tmp->neighbours[j]->sps == 1
					&& tmp->neighbours[j] != map->start)
					{
						*changed = 1;
						j -= del_tube(tmp, tmp->neighbours[j], map);
					}
					j++;
				}
			}
			if (tmp->spe == 1 && tmp != map->end)
			{
				j = 0;
				while (j < tmp->neighbours_len)
				{
					if (tmp->neighbours[j] != NULL
					&& tmp->neighbours[j]->spe == 1
					&& tmp->neighbours[j] != map->end)
					{
						*changed = 1;
						j -= del_tube(tmp, tmp->neighbours[j], map);
					}
					j++;
				}
			}
		}
		i++;
	}
}

ssize_t			remove_unnecessary_tubes(t_map *map, int *changed)
{
	BITFIELD_TYPE	*visited;
	t_conn_wrap		*qr;

	// set_weights(map, 1);
	*changed = 0;
	remove_sps_spe_conns(map, changed);
	if (setup_q_un(&qr, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	print_connection_queue(qr->q);
	if (un_add_start_nbs_to_q(map->start, qr, map, changed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// print_connection_queue(qr->q);
	// exit (0);
	// print_map(map);
	execute_queue_un(qr, map, changed);
	// while (*q)
	// {
	// 	// printf("QUEUE ITEM dst %s src %s dist %lu\n", (*q)->dst->name,
	// 	// (*q)->src->name, (*q)->dist);
	// 	del_un_tubes(*q, changed, map);
	// 	printf("Add to bitfield %s\n", (*q)->dst->name);
	// 	// add_to_bitfield((*q)->dst, visited);
	// 	if (un_add_nbs_to_queue((*q)->dst, q, visited, map) == EXIT_FAILURE)
	// 		return (EXIT_FAILURE);
	// 	remove_q_item_un(q, *q);
	// 	// exit (0);
	// }
	// print_map(map);
	// exit (0);
	return (EXIT_SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   del_un_tubes.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 16:25:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/04 16:25:25 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int		remove_if_un(t_connection *src_side,
t_connection *nb_src, t_connection *side_nb, t_map *map)
{
	int		add_opt_nb_side;
	int		add_opt_side_nb;
	int		changed;

	changed = 0;
	if (DEBUG == 1)
	{
		printf("\n\nREMOVE IF UN\n");
		printf("SRC %s SIDE %s NB %s\n", src_side->src->name, src_side->dst->name,
		side_nb->dst->name);
	}
	add_opt_nb_side = alt_opts_nb(side_nb, src_side, nb_src, map, &changed);
	add_opt_side_nb = alt_opts_side(side_nb, src_side, map, &changed);
	if (DEBUG == 1)
		printf("Add opt nb side %d Add opt side nb %d\n", add_opt_nb_side, add_opt_side_nb);
	if (add_opt_nb_side == 0 && add_opt_side_nb == 0)
	{
		// if (shrt_conn_dsts_nb(src_side, nb_src, side_nb) == 0
		// && has_conn_to(side_nb->src, side_nb->src_nb) == 1)
		// {
		// 	printf("Not better to go through nb\n");
		// 	changed = 1;
		// 	del_tube(side_nb->src, side_nb->src_nb, map);
		// }
		// if (shrt_conn_dsts_side(src_side, nb_src, side_nb) == 0
		// && has_conn_to(side_nb->dst, side_nb->dst_nb) == 1)
		// {
		// 	printf("Not better to go through side\n");
		// 	changed = 1;
		// 	del_tube(side_nb->dst, side_nb->dst_nb, map);
		// }
		if (DEBUG == 1)
			printf("Neither adds option to other\n");
		changed = rm_un_conn(side_nb, src_side, nb_src, map);
		if (DEBUG == 1)
			printf("\n\nchanged after rm un conn %d\n\n", changed);
	}
	else if (add_opt_nb_side == 0 &&
	(nb_src->src != map->end && nb_src->src != map->start))
	{
		//&& cause_for_removal_side_to_nb(src_side, side_nb, nb_src) == 1
		if (DEBUG == 1)
			printf("nb doesnt add option to side\n");
		if (shrt_conn_dsts_nb(src_side, nb_src, side_nb, map) == 0
		&& has_conn_to(side_nb->src, side_nb->src_nb) == 1)
		{
			changed = 1;
			del_tube(side_nb->src, side_nb->src_nb, map);
			/* MAKE SURE THIS IS OKAY!!*/
			if (side_nb->dist != 1)
				del_tube(side_nb->dst_nb, side_nb->dst, map);
		}
	}
	else if (add_opt_side_nb == 0 &&
	(side_nb->src != map->end && side_nb->src != map->start))
	{
		//&& cause_for_removal_nb_to_dst(src_side, side_nb, nb_src) == 1
		if (DEBUG == 1)
			printf("side doesnt add option to nb side %s\n", side_nb->src->name);
		if (shrt_conn_dsts_side(src_side, nb_src, side_nb, map) == 0
		&& has_conn_to(side_nb->dst, side_nb->dst_nb) == 1)
		{
			if (DEBUG == 1)
			{
				printf("Not better to go through side\n");
				print_connection(side_nb);
			}
			changed = 1;
			del_tube(side_nb->dst, side_nb->dst_nb, map);
			/* MAKE SURE THIS IS OKAY!!*/
			if (side_nb->dist != 1)
				del_tube(side_nb->src_nb, side_nb->src, map);
		}
		// exit (0);
	}
	return (changed);
}

static int			remove_dupl_path(t_connection *side_nb, t_connection *q, t_map *map,
int *changed)
{
	if (side_nb->dist < q->dist)
	{
		*changed = 1;
		if (DEBUG == 1)
			printf("DELETE Q PATH\n");
		del_tube(q->dst, q->dst_nb, map);
		del_tube(q->dst_nb, q->dst, map);
		del_tube(q->src, q->src_nb, map);
		del_tube(q->src_nb, q->src, map);
		// q->src = side_nb->src;
		// q->src_nb = side_nb->src_nb;
		// q->dst = side_nb->dst;
		// q->dst_nb = side_nb->dst_nb;
		// q->dist = side_nb->dist;
		return (0);
	}
	else
	{
		*changed = 1;
		del_tube(side_nb->dst, side_nb->dst_nb, map);
		del_tube(side_nb->dst_nb, side_nb->dst, map);
		del_tube(side_nb->src, side_nb->src_nb, map);
		del_tube(side_nb->src_nb, side_nb->src, map);
		return (1);
	}
}

static int	update_src_path(t_connection *q, t_map *map, int *changed,
size_t *i)
{
	if (DEBUG == 1)
	{
		printf("UPDATE\n");
		print_connection(q);
	}
	if (q->dst->is_junction == 0)
	{
		find_real_nb(q, map);
		if (DEBUG == 1)
			printf("after find real nb\n");
		*i = -1;
		if (q->dst == NULL)
		{
			if (DEBUG == 1)
				printf("NOWHERE TO GO update src nb dst nb %s src nb %s\n", q->src_nb->name, q->dst_nb->name);
			/* Removes different connections.... */
			handle_nowhere_to_go(q->src, q->src_nb, map);
			// del_tube(q->src_nb, q->dst_nb, map);
			// del_tube(q->dst_nb, q->src_nb, map);
			return (0);
		}
		if (q->src == q->dst)
		{
			if (DEBUG == 1)
				printf("loop\n");
			*changed = 1;
			handle_loop_no_ret(q, map, changed);
			// del_tube(q->dst, q->dst_nb, map);
			// del_tube(q->src, q->src_nb, map);
			return (0);
		}
	}
	return (1);
}

void	handle_loop(t_connection *conn, t_map *map, int *changed, size_t *i)
{
	del_tube(conn->dst, conn->dst_nb, map);
	del_tube(conn->dst_nb, conn->dst, map);
	del_tube(conn->src, conn->src_nb, map);
	del_tube(conn->src_nb, conn->src, map);
	*changed = 1;
	*i = -1;
}

void	handle_loop_no_ret(t_connection *conn, t_map *map, int *changed)
{
	del_tube(conn->dst, conn->dst_nb, map);
	del_tube(conn->dst_nb, conn->dst, map);
	del_tube(conn->src, conn->src_nb, map);
	del_tube(conn->src_nb, conn->src, map);
	*changed = 1;
}

int			del_un_tubes(t_connection *q, int *changed, t_map *map)
{
	size_t			i;
	size_t			prev_i;
	int				res;
	t_room			*prev;
	t_connection 	side_nb;
	t_connection	nb_src;

	i = 0;
	res = 0;
	prev = NULL;
	prev_i = 0;
	if (DEBUG == 1)
		printf("DEL TUBE\n");
	setup_conn(&side_nb, q->dst);
	while (i < q->dst->neighbours_len)
	{
		setup_conn(&side_nb, q->dst);
		if (q->dst->neighbours[i] != NULL && q->dst->neighbours[i] != q->dst_nb)
		{
			set_conn(&side_nb, q->dst->neighbours[i]);
			if (q->dst->neighbours[i]->is_junction == 0)
				find_real_nb(&side_nb, map);
			if (side_nb.dst == NULL)
			{
				if (DEBUG == 1)
					printf("nowhere to go del un tubes\n");
				handle_nowhere_to_go(side_nb.src, side_nb.src_nb, map);
					// exit (0);
			}
			if (side_nb.dst == side_nb.src)
			{
				/* Is loop from dst so doesnt affect iter */
				handle_loop(&side_nb, map, changed, &i);
			}
			else if (side_nb.dst == q->src && side_nb.src == q->dst
			&& !(q->src == map->start && q->dst == map->end))
			{
				if (DEBUG == 1)
				{
					printf("REMOVE DUPLICATE PATH\n");
					printf("q\n");
					printf("side to nb\n");
				}
				prev_i = i;
				i -= remove_dupl_path(&side_nb, q, map, changed);
				if (prev_i == i)
					return (1);
				if (DEBUG == 1)
					print_connection(q);
			}
			else
			{
				if (DEBUG == 1)
				{
					printf("REGULAR ROUTE\n");
					printf("Conn src to side\n");
					print_connection(q);
					printf("Conn side to nb\n");
					print_connection(&side_nb);
				}
				setup_conn(&nb_src, side_nb.dst);
				if (is_nb_of_src(&side_nb, q, &nb_src, map, changed) == 1)
				{
					if (DEBUG == 1)
						printf("NB IS CONNECTED TO SRC\n");
					prev = q->dst->neighbours[i];
					res = remove_if_un(q, &nb_src, &side_nb, map);
					if (q->dst->neighbours[i] != prev)
						i--;
					if (*changed == 0)
						*changed = res;
				}
				else
				{
					if (DEBUG == 1)
						printf("NOT NB OF SRC\n");
				}
			}
			if (update_src_path(q, map, changed, &i) == 0)
			{
				if (DEBUG == 1)
					printf("Path we tried to update became loop or can't go anywhere\n");
				return (1);
			}
		}
		i++;
	}
	return (1);
}

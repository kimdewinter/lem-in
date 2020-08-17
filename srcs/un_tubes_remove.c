/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_tubes_remove.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 15:46:16 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/17 21:43:27 by lravier       ########   odam.nl         */
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

static void		compr_side_dst(t_diamond *curr)
{
	set_conn(&(curr->nb_dst), curr->curr_nb_nb);
	if (curr->side_dst.dst == curr->nb_dst.dst)
	{
		curr->common_dst_found = 1;
		if ((curr->side_dst.dist + curr->side_nb->dist) < curr->nb_dst.dist)
			curr->nb_improved_by_side++;
		if ((curr->nb_dst.dist + curr->side_nb->dist) < curr->side_dst.dist)
			curr->side_improved_by_nb++;
	}
}

static void		compr_nb_side_dst(t_diamond *curr)
{
	size_t	j;

	set_conn(&curr->side_dst, curr->curr_nb_side);
	j = 0;
	while (j < curr->nb_src->src->neighbours_len)
	{
		setup_conn(&curr->nb_dst, curr->nb_src->src);
		if (curr->nb_src->src->neighbours[j] != NULL
			&& check_dst_src(curr->side_nb, curr->nb_src,
			curr->nb_src->src->neighbours[j]) == 0)
		{
			curr->curr_nb_nb = curr->nb_src->src->neighbours[j];
			compr_side_dst(curr);
		}
		j++;
	}
}

static void		rm_found_un_conn(t_diamond *curr, int *changed, t_map *map)
{
	if (curr->nb_improved_by_side == 0
	&& (curr->src_side->dst != map->end && curr->src_side->dst != map->start)
	&& has_conn_to(curr->side_nb->dst, curr->side_nb->dst_nb) == 1)
	{
		printf("nb through side doesnt help\n");
		*changed = 1;
		del_tube(curr->side_nb->dst, curr->side_nb->dst_nb, map);
		if (curr->side_nb->dist != 1)
			del_tube(curr->side_nb->dst_nb, curr->side_nb->dst, map);
	}
	if (curr->side_improved_by_nb == 0
	&& (curr->nb_dst.src != map->end && curr->nb_dst.src != map->start)
	&& has_conn_to(curr->side_nb->src, curr->side_nb->src_nb) == 1)
	{
		printf("side through nb doesnt help\n");
		*changed = 1;
		del_tube(curr->side_nb->src, curr->side_nb->src_nb, map);
		if (curr->side_nb->dist != 1)
			del_tube(curr->side_nb->src_nb, curr->side_nb->src, map);
	}
}

void			rm_un_conn(t_triangle *tr, t_map *map, int *changed)
{
	t_diamond		curr;
	size_t			i;

	i = 0;
	setup_diamond(&curr, &tr->side_nb, tr->src_side, &tr->nb_src);
	printf("Neither adds options\n");
	while (i < curr.side_nb->src->neighbours_len)
	{
		setup_conn(&curr.side_dst, curr.side_nb->src);
		if (curr.side_nb->src->neighbours[i] != NULL
		&& check_dst_src(curr.src_side, curr.side_nb,
		curr.side_nb->src->neighbours[i]) == 0)
		{
			curr.curr_nb_side = curr.side_nb->src->neighbours[i];
			compr_nb_side_dst(&curr);
		}
		i++;
	}
	if (curr.common_dst_found == 1)
		rm_found_un_conn(&curr, changed, map);
}

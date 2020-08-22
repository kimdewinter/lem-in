/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_remove_if_un.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 14:36:59 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/22 16:02:12 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void	handle_side_through_nb(t_triangle *tr, int *changed, t_map *map)
{
	if (shrt_conn_dsts_nb(tr->src_side, &tr->nb_src, &tr->side_nb) == 0
	&& has_conn_to(tr->side_nb.src, tr->side_nb.src_nb) == 1)
	{
		// *changed = 1;
		// if (tr->side_nb.src->dist_to_start <= tr->side_nb.dst->dist_to_start)
		// 	printf("side %s is closer or equal to start %s\n", tr->side_nb.src->name,
		// 	tr->side_nb.dst->name);
		set_unavailable(tr->side_nb.src, tr->side_nb.src_nb, changed, map);
		// del_tube(tr->side_nb.src, tr->side_nb.src_nb, map);
		if (tr->side_nb.dist != 1)
			set_unavailable(tr->side_nb.dst_nb, tr->side_nb.dst, changed, map);
	}
}

static void	handle_nb_through_side(t_triangle *tr, int *changed, t_map *map)
{
	if (shrt_conn_dsts_side(tr->src_side, &tr->nb_src, &tr->side_nb) == 0
	&& has_conn_to(tr->side_nb.dst, tr->side_nb.dst_nb) == 1)
	{
		// *changed = 1;
		// if (tr->side_nb.dst->dist_to_start <= tr->side_nb.src->dist_to_start)
		// 	printf("nb %s is closer or equal to start %s\n", tr->side_nb.dst->name,
		// 	tr->side_nb.src->name);
		set_unavailable(tr->side_nb.dst, tr->side_nb.dst_nb, changed, map);
		// del_tube(tr->side_nb.dst, tr->side_nb.dst_nb, map);
		if (tr->side_nb.dist != 1)
			set_unavailable(tr->side_nb.src_nb, tr->side_nb.src, changed, map);
	}
}

void		remove_if_un(t_triangle *tr, t_map *map, int *changed)
{
	int		add_opt_nb_side;
	int		add_opt_side_nb;

	// printf("\nRemove if un SRC %s\n\n", tr->src_side->src->name);
	add_opt_nb_side = alt_opts_nb(tr, map, changed);
	add_opt_side_nb = alt_opts_side(&tr->side_nb, tr->src_side, map, changed);
	// print_triangle(tr);
	printf("Alt opt side %s %d\nAlt opt nb %s %d\n", tr->side_nb.src->name, add_opt_side_nb,
	tr->side_nb.dst->name, add_opt_nb_side);
	if (add_opt_nb_side == 0 && add_opt_side_nb == 0)
		rm_un_conn(tr, map, changed);
	else if (add_opt_nb_side == 0 &&
	(tr->nb_src.src != map->end && tr->nb_src.src != map->start))
		handle_side_through_nb(tr, changed, map);
	else if (add_opt_side_nb == 0 &&
	(tr->side_nb.src != map->end && tr->side_nb.src != map->start))
		handle_nb_through_side(tr, changed, map);
	// exit (0);
}

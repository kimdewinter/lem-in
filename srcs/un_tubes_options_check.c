/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_tubes_options_check.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 16:13:52 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/13 19:24:07 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		alt_opts_side(t_connection *side_nb, t_connection *src_side, t_map *map,
int *changed)
{
	size_t			i;
	t_connection	side_dst;

	i = 0;
	setup_conn(&side_dst, src_side->dst);
	while (i < side_dst.src->neighbours_len)
	{
		setup_conn(&side_dst, src_side->dst);
		if (check_dst_src(src_side, &side_dst,
		side_dst.src->neighbours[i]) == 0)
		{
			set_conn(&side_dst, side_dst.src->neighbours[i]);
			if (check_conn(&side_dst, &i, changed, map) == 1)
			{
				if (side_dst.dst != side_nb->dst
				&& side_dst.dst != src_side->src
				&& is_nb_of_other(side_dst.dst, side_nb->dst, map, changed)
				== 0)
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int		alt_opts_nb(t_triangle *curr, t_map *map, int *changed)
{
	size_t			i;
	t_connection	nb_dst;

	i = 0;
	setup_conn(&nb_dst, curr->nb_src.src);
	while (i < nb_dst.src->neighbours_len)
	{
		setup_conn(&nb_dst, curr->nb_src.src);
		if (check_dst_src(curr->src_side, &curr->side_nb,
		nb_dst.src->neighbours[i]) == 0)
		{
			set_conn(&nb_dst, nb_dst.src->neighbours[i]);
			if (check_conn(&nb_dst, &i, changed, map) == 1)
			{
				if (nb_dst.dst != curr->side_nb.src
				&& nb_dst.dst != curr->nb_src.dst
				&& is_nb_of_other(nb_dst.dst, curr->side_nb.src,
				map, changed) == 0)
					return (1);
			}
		}
		i++;
	}
	return (0);
}

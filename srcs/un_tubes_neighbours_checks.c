/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_tubes_neighbours_checks.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 16:55:54 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/22 11:14:30 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		is_nb_of_src(t_triangle *curr, t_map *map, int *changed)
{
	ssize_t			i;

	i = 0;
	// printf("IS NB OF SRC\n");
	setup_conn(&curr->nb_src, curr->side_nb.dst);
	if (room_in_bitfield(curr->src_side->src, curr->nb_src.src->removed_conns)
	== 1)
		return (0);
	while ((size_t)i < curr->nb_src.src->neighbours_len)
	{
		setup_conn(&curr->nb_src, curr->side_nb.dst);
		if (curr->nb_src.src->neighbours[i] != curr->side_nb.dst
		&& curr->nb_src.src->neighbours[i] != curr->side_nb.dst_nb)
		{
			set_conn(&curr->nb_src, curr->nb_src.src->neighbours[i]);
			if (check_conn(&curr->nb_src, &i, changed, map) == 1)
			{
				if (curr->nb_src.dst == curr->src_side->src)
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int		is_nb_of_other(t_room *dst, t_room *curr, t_map *map, int *changed)
{
	ssize_t			i;
	t_connection	tmp;

	i = 0;
	// printf("IS NB OF OTHER\n");
	setup_conn(&tmp, curr);
	if (room_in_bitfield(dst, curr->removed_conns) == 1)
		return (0);
	while ((size_t)i < curr->neighbours_len)
	{
		setup_conn(&tmp, curr);
		set_conn(&tmp, curr->neighbours[i]);
		if (check_conn(&tmp, &i, changed, map) == 1)
		{
			if (tmp.dst == dst)
				return (1);
		}
		i++;
	}
	return (0);
}

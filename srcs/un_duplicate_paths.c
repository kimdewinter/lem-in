/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_duplicate_paths.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 15:16:08 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/20 12:10:45 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int			is_not_to_dst_or_src(t_connection **conn, t_dupl *paths)
{
	if ((*conn)->dst->neighbours[paths->j] != (*conn)->dst_nb
	&& (*conn)->dst->neighbours[paths->j] != (*conn)->src_nb
	&& paths->j != paths->i)
		return (1);
	return (0);
}

static void			remove_duplicate_path_if_un(t_dupl *paths,
t_connection **conn, int *changed, t_map *map)
{
	// printf("REMOVE DUPLICATE PATH IF UN\n");
	// print_connection(*conn);
	setup_conn(&paths->other, (*conn)->dst);
	if (is_not_to_dst_or_src(conn, paths) == 1
	&& room_in_bitfield((*conn)->dst->neighbours[paths->j], (*conn)->dst->unavailable) == 0)
	{
		set_conn(&paths->other, (*conn)->dst->neighbours[paths->j]);
		if (check_conn(&paths->curr, &paths->j, changed, map) == 1)
		{
			// printf("CHECK CONN ++ OK\n");
			if (paths->curr.dst == paths->other.dst)
			{
				if (paths->curr.dist < paths->other.dist)
				{
					*changed = 1;
					remove_path(&paths->other, map);
					paths->j--;
				}
				else
				{
					*changed = 1;
					remove_path(&paths->curr, map);
					paths->curr = paths->other;
					paths->i = 0;
				}
			}
		}
		// print_connection(*conn);
	}
	// printf("REMOVE DUPLICATE PATH IF UN AFTER\n");
}

void				remove_duplicate_paths(t_connection **conn, t_map *map,
int *changed)
{
	t_dupl		paths;

	// printf("REMOVE DUPLICATE PATHS\n");
	// print_connection(*conn);
	setup_conn(&paths.curr, (*conn)->dst);
	paths.i = 0;
	paths.j = 0;
	while (paths.i < (*conn)->dst->neighbours_len)
	{
		setup_conn(&paths.curr, (*conn)->dst);
		if ((*conn)->dst->neighbours[paths.i] != (*conn)->dst_nb
		&& (*conn)->dst->neighbours[paths.i] != (*conn)->src_nb
		&& room_in_bitfield((*conn)->dst->neighbours[paths.i], (*conn)->dst->unavailable) == 0)
		{
			set_conn(&paths.curr, (*conn)->dst->neighbours[paths.i]);
			// print_connection(&paths.curr);
			if (check_conn(&paths.curr, &paths.i, changed, map) == 1)
			{
				paths.j = 0;
				while (paths.j < (*conn)->dst->neighbours_len)
				{
					remove_duplicate_path_if_un(&paths, conn, changed, map);
					paths.j++;
				}
			}
		}
		paths.i++;
	}
}

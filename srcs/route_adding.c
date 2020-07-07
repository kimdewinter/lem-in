/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_adding.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:34:22 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/07 13:56:50 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t				handle_path_src(t_subpath *path, t_queue *item,
t_map *map, t_subpath **new)
{
	if (item->src->is_conj == 0 && item->src != map->end)
	{
		if (add_to_path(path, item->src, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		path->sp = 1;
		item->src = path->conj;
		path->added_this_turn = 1;
		(*new) = path;
	}
	else
	{
		if (item->src != map->end)
		{
			if (create_new_path(new, path, item->src, map) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
		{
			(*new) = path;
			(*new)->added_this_turn = 1;
		}
	}
	return (EXIT_SUCCESS);
}

static size_t		handle_path_dst(size_t round, t_queue *item, t_map *map,
t_subpath **new, int *add)
{
	if (item->dst != map->start && (item->dst->is_conj == 0 ||
	(item->dst->checked == 0 && is_junction(item->dst, round) == 0)))
	{
		item->dst->is_conj = 0;
		(*new)->sp = 1;
		if (add_nodes_to_path(item, new, map, add) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

size_t				add_path(t_qwrap *qr, t_queue *item, t_subpath *path,
t_map *map)
{
	t_subpath	*new;
	int			add;

	new = NULL;
	add = 1;
	path->added_this_turn = 0;
	if (handle_path_src(path, item, map, &new) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (handle_path_dst(qr->round, item, map, &new, &add) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (room_in_bitfield(new->conj, item->dst->bitconj) == 1)
		solve_conflict(item, new, &add);
	else if (item->dst->spe == 1 && item->dst != map->start)
		solve_spe_conflict(item, new, map, &add);
	if (add == 1)
	{
		if (add_path_to_room(item, map, &new) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		item->path = new;
	}
	// else
	// {
	// 	// item->path = NULL;
	// 	// remove_queue_item(qr, item);
	// 	// exit (0);
	// }
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_setup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 13:45:50 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/28 14:55:01 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t		add_items_start(t_qwrap **qr, t_room *curr, t_map *map)
{
	size_t		i;
	t_subpath	*pt;

	i = 0;
	while (i < curr->neighbours_len)
	{
		if (room_in_bitfield(curr->neighbours[i], (*qr)->visited) == 0
		&& !(curr->sps == 1 && curr->neighbours[i] != map->start)
		&& curr->neighbours[i]->dead_end == 0)
		{
			if (create_new_path(&pt, curr->routes[0], curr, map) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			pt->end = curr;
			if (add_to_queue(*qr, curr, curr->neighbours[i], pt) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void		add_other_nbs_to_visited(t_qwrap *qr, t_room *src, t_room *dst)
{
	size_t	i;

	i = 0;
	while (i < src->neighbours_len)
	{
		if (src->neighbours[i] != dst)
			add_to_bitfield(src->neighbours[i], qr->visited);
		i++;
	}
}

ssize_t		setup_queue(t_qwrap **qr, t_room *curr, t_map *map)
{
	t_subpath	*pt;

	pt = NULL;
	if (create_new_path(&pt, NULL, map->end, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (add_path_to_room(curr, map, &pt) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*qr = (t_qwrap *)malloc(sizeof(t_qwrap));
	if (*qr)
	{
		(*qr)->queue = (t_queue **)malloc(sizeof(t_queue *));
		(*qr)->items = 0;
		(*qr)->last = NULL;
		if ((*qr)->queue)
		{
			*((*qr)->queue) = NULL;
			if (bite_alloc(&((*qr)->visited), map) == EXIT_SUCCESS)
			{
				add_to_bitfield(map->end, (*qr)->visited);
				add_other_nbs_to_visited(*qr, map->end, curr);
				if (add_items_start(qr, curr, map) == EXIT_SUCCESS)
				{
					add_to_bitfield(curr, (*qr)->visited);
					return (EXIT_SUCCESS);
				}
			}
		}
		free ((*qr)->queue);
	}
	free (*qr);
	return (EXIT_FAILURE);
}

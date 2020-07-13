/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_setup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 13:45:50 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/13 13:09:40 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t		add_items_start(t_qwrap **qr, t_map *map)
{
	size_t		i;
	t_queue		*new;

	i = 0;
	new = NULL;
	map->end->weight = (*qr)->round;
	while (i < map->end->neighbours_len)
	{
		if (map->end->neighbours[i]->dead_end == 0)
		{
			new = new_queue_item(NULL,
			map->end->neighbours[i], map->end);
			if (new)
				add_item_queue(qr, new);
			else
				return (EXIT_FAILURE);
		}
		map->end->neighbours[i]->weight = (*qr)->round;
		i++;
	}
	return (EXIT_SUCCESS);
}

ssize_t		setup_queue(t_qwrap **qr, t_map *map)
{
	*qr = (t_qwrap *)malloc(sizeof(t_qwrap));
	if (*qr)
	{
		(*qr)->queue = (t_queue **)malloc(sizeof(t_queue *));
		(*qr)->items = 0;
		(*qr)->last = NULL;
		(*qr)->round = 1;
		if ((*qr)->queue)
		{
			*((*qr)->queue) = NULL;
			if (map->end->sps == 1)
				return (EXIT_SUCCESS);
			if (add_items_start(qr, map) == EXIT_SUCCESS)
			{
				map->end->dead_end = 1;
				return (EXIT_SUCCESS);
			}
		}
		free ((*qr)->queue);
	}
	free (*qr);
	return (EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 11:45:52 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/01 10:28:48 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

t_queue		*new_queue_item(t_subpath *pt, t_room *dst, t_room *src)
{
	t_queue	*new;

	printf("NEW QUEUE ITEM\n");
	new = (t_queue *)malloc(sizeof(t_queue));
	if (new)
	{
		new->handled = 0;
		new->src = src;
		new->dst = dst;
		new->path = pt;
		new->next = NULL;
		new->prev = NULL;
		return (new);
	}
	return (NULL);
}

void		add_item_queue(t_qwrap **qr, t_queue *new)
{
	t_queue	*tmp;

	tmp = (*qr)->last;
	(*qr)->items++;
	if (tmp == NULL)
	{
		(*qr)->last = new;
		*((*qr)->queue) = new;
	}
	else
	{
		(*qr)->last->next = new;
		new->prev = (*qr)->last;
		(*qr)->last = new;
	}
	// if ((*qr)->last)
	// 	printf("last %s", (*qr)->last->dst->name);
	// if ((*(*qr)->queue))
	// 	printf("\nfirst %s\n", (*(*qr)->queue)->dst->name);
}

static size_t		add_items_start(t_qwrap **qr, t_map *map)
{
	size_t		i;
	t_queue		*new;

	i = 0;
	new = NULL;
	map->end->weight = (*qr)->round;
	while (i < map->end->neighbours_len)
	{
		if (map->end->neighbours[i]->nb->dead_end == 0)
		{
			new = new_queue_item(NULL,
			map->end->neighbours[i]->nb, map->end);
			if (new)
				add_item_queue(qr, new);
			else
				return (EXIT_FAILURE);
		}
		// map->end->neighbours[i]->available = 0;
		map->end->neighbours[i]->nb->weight = (*qr)->round;
		i++;
	}
	return (EXIT_SUCCESS);
}

size_t		setup_queue(t_qwrap **qr, t_map *map)
{
	printf("Setup queue\n");
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
				printf("After setup queue\n");
				print_queue(*qr);
				map->end->dead_end = 1;
				return (EXIT_SUCCESS);
			}
		}
		free ((*qr)->queue);
	}
	free (*qr);
	return (EXIT_FAILURE);
}
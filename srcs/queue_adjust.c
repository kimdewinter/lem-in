/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_adjust.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 12:35:53 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/16 21:37:37 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t			add_nbs_to_queue(t_qwrap *qr, t_queue *curr, t_map *map)
{
	size_t		i;

	i = 0;
	if (curr->dst == map->start)
		return (EXIT_SUCCESS);
	while (i < curr->dst->neighbours_len)
	{
		if (curr->dst->neighbours[i]->dead_end == 0)
		{
			if (add_nb_to_queue(map, curr, curr->dst->neighbours[i], qr)
			== EXIT_FAILURE)
			{
				printf("Can be added\n");
				return (EXIT_FAILURE);
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	set_weights_nbs(t_queue **queue, t_map *map)
{
	t_queue	*iter;
	size_t	i;

	iter = *queue;
	while (iter)
	{	
		i = 0;
		if (iter->dst != map->start)
		{
			while (i < iter->dst->neighbours_len)
			{
				if (iter->dst->neighbours[i] != map->start 
				&& (iter->dst->neighbours[i]->weight == 0 ||
				iter->dst->weight < iter->dst->neighbours[i]->weight))
					iter->dst->neighbours[i]->weight = iter->dst->weight + 1;
				i++;
			}
		}
		iter = iter->next;
	}
}

void		initialize_in_queue(t_qwrap *qr, t_map *map)
{
	size_t i;

	i = 0;
	while (i < map->bitfield_len)
	{
		qr->in_queue[0] = (BITFIELD_TYPE)0;
		i++;
	}
}

ssize_t		adjust_queue(t_qwrap *qr, t_map *map, size_t len)
{
	t_queue			*curr;
	t_queue			*prev;
	size_t			i;

	initialize_in_queue(qr, map);
	curr = *(qr->queue);
	i = 0;
	prev = NULL;
	qr->round++;
	set_weights_nbs(qr->queue, map);
	while (i < len)
	{
		if (add_nbs_to_queue(qr, curr, map)
		== EXIT_FAILURE)
			return (EXIT_FAILURE);
		prev = curr;
		curr = curr->next;
		remove_queue_item(qr, prev);
		i++;
	}
	printf("AFTER ADJUST\n");
	print_queue(qr);
	return (EXIT_SUCCESS);
}

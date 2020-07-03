/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_adjust.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 12:35:53 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/03 16:37:07 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int				is_viable_nb(t_queue *curr, size_t i,
size_t round)
{
	if (!(curr->dst->neighbours[i]->dead_end == 0
	&& (curr->dst->neighbours[i]->weight == 0
	|| curr->dst->neighbours[i]->weight > curr->dst->weight 
	|| (curr->dst->neighbours[i]->weight < curr->dst->weight &&
	curr->dst->weight > round))))
	{
		return (0);
	}
	return (1);
}

static size_t			add_nbs_to_queue(t_qwrap *qr, t_queue *curr, t_map *map)
{
	size_t		i;
	size_t		j;

	i = 0;
	curr->dst->viable_nbs = curr->dst->neighbours_len;
	while (i < curr->dst->neighbours_len)
	{
		j = 0;
		while (j < curr->dst->num_options)
		{
			if (curr->dst->routes[j]->added_this_turn == 1)
			{
				if (curr->dst == map->start)
					return (EXIT_SUCCESS);
				if (is_viable_nb(curr, i, qr->round) == 1 &&
				is_viable_for_path(map, curr, curr->dst->neighbours[i],
				curr->dst->routes[j]) == 1)
				{
					if (add_to_queue(qr, curr->dst,
					curr->dst->neighbours[i], curr->dst->routes[j])
					== EXIT_FAILURE)
						return (EXIT_FAILURE);
				}
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	set_weights_after(t_queue **queue, t_map *map)
{
	t_queue	*iter;

	iter = *queue;
	while (iter)
	{
		if (iter->dst != map->start)
		{
			if (iter->src->weight < iter->dst->weight || iter->dst->weight == 0)
				iter->dst->weight = iter->src->weight + 1;
		}
		iter = iter->next;
	}
}

size_t		adjust_queue(t_qwrap *qr, t_map *map, size_t len)
{
	t_queue			*curr;
	t_queue			*prev;
	size_t			i;
	BITFIELD_TYPE	*visited;

	if (bite_alloc(&visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	curr = *(qr->queue);
	i = 0;
	prev = NULL;
	qr->round++;
	while (i < len)
	{
		if (room_in_bitfield(curr->dst, visited) == 0)
		{
			if (add_nbs_to_queue(qr, curr, map)
			== EXIT_FAILURE)
				return (EXIT_FAILURE);
			add_to_bitfield(curr->dst, visited);
		}
		prev = curr;
		curr = curr->next;
		remove_queue_item(qr, prev);
		i++;
	}
	set_weights_after(qr->queue, map);
	free (visited);
	return (EXIT_SUCCESS);
}
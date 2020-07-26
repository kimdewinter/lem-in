/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_adjust.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 12:35:53 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/26 16:26:31 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t			add_nbs_to_queue(t_qwrap *qr, t_queue *curr, t_map *map)
{
	size_t		i;
	t_subpath	*new;

	i = 0;
	curr->dst->viable_nbs = curr->dst->neighbours_len;
	while (i < curr->dst->neighbours_len)
	{
		if (curr->dst == map->start)
			return (EXIT_SUCCESS);
		if (room_in_bitfield(curr->dst->neighbours[i], qr->visited) == 0
		&& !(curr->dst->sps == 1 && curr->dst->neighbours[i] != map->start)
		&& curr->dst->neighbours[i]->dead_end == 0)
		{
			if (create_new_path(&new, curr->path, curr->dst, map)
			== EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (add_to_queue(qr, curr->dst,
			curr->dst->neighbours[i], new)
			== EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	set_visited(t_qwrap *qr, t_map *map)
{
	t_queue	*iter;

	iter = *(qr->queue);
	while (iter)
	{
		if (iter->dst != map->start)
			add_to_bitfield(iter->dst, qr->visited);
		iter = iter->next;
	}
}

ssize_t		adjust_queue(t_qwrap *qr, t_map *map, size_t len)
{
	t_queue			*curr;
	t_queue			*prev;
	size_t			i;

	curr = *(qr->queue);
	i = 0;
	prev = NULL;
	set_visited(qr, map);
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
	return (EXIT_SUCCESS);
}
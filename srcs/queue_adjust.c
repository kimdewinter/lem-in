/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_adjust.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 12:35:53 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/30 13:42:04 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int				has_other_options(t_room *candidate,
t_room *side, t_room *dst, t_room *src, t_map *map)
{
	size_t	i;

	i = 0;
	if (candidate->is_conj == 0)
		return (0);
	// printf("candidate %s side %s dst %s src %s\n", candidate->name, side->name,
	// dst->name, src->name);
	while (i < candidate->neighbours_len)
	{
		if (candidate->neighbours[i]->dead_end == 0
		&& candidate->neighbours[i] != side
		&& candidate->neighbours[i] != dst
		&& candidate->neighbours[i] != src
		&& !(candidate->sps == 1 && candidate->neighbours[i] != map->start))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static int				queue_conflict(t_qwrap *qr, t_room *dst, t_room *src,
t_room *nb, t_map *map)
{
	t_queue	*iter;
	int		options_queue;
	int		options_new;

	iter = qr->last;
	options_new = 0;
	options_queue = 0;
	while (iter && iter->handled == 0)
	{
		if (iter->dst == nb)
		{
			// printf("iter dst == nb\n");
			// print_path(iter->path);
			if (iter->path && iter->path->next && iter->path->next->conj == src)
			{
				// print_path(iter->path);
				// printf("stuff\n");
				/* 4, 5, 1, 7 */
				options_queue = has_other_options(iter->path->conj, dst, nb, src,
				map);
				// printf("Queue has options: %d\n", options_queue);
				/* 5, 4, 1, 7 */
				options_new = has_other_options(dst, iter->path->conj, nb, src,
				map);
				// printf("Curr has options: %d\n", options_new);
				if (options_new == 1 && options_queue == 1)
				{
					return (0);
				}
				if (options_new == 0 && options_queue == 0)
				{
					return (1);
				}
				if (options_new == 1 && options_queue == 0)
					return (1);
				if (options_new == 0 && options_queue == 1)
				{
					free (iter->path);
					remove_queue_item(qr, iter);
					return (0);
				}
			}
		}
		iter = iter->prev;
	}
	return (0);
}

static void				remove_start_end_nb(t_subpath *pt)
{
	pt->bitconj[pt->start->room_i / BITFIELD_SIZE] ^= ((BITFIELD_TYPE)1
	<< (63 - pt->start->room_i % BITFIELD_SIZE));
	pt->bitconj[pt->end->room_i / BITFIELD_SIZE] ^= ((BITFIELD_TYPE)1
	<< (63 - pt->end->room_i % BITFIELD_SIZE));
}

static ssize_t			add_nbs_to_queue(t_qwrap *qr, t_queue *curr, t_map *map,
BITFIELD_TYPE *visited)
{
	size_t		i;
	t_subpath	*new;
	int			add;

	i = 0;
	curr->dst->viable_nbs = curr->dst->neighbours_len;
	while (i < curr->dst->neighbours_len)
	{
		add = 1;
		if (curr->dst == map->start)
		{
			remove_start_end_nb(curr->path);
			return (EXIT_SUCCESS);
		}
		if (room_in_bitfield(curr->dst->neighbours[i], qr->visited) == 0
		&& !(curr->dst->sps == 1 && curr->dst->neighbours[i] != map->start)
		&& curr->dst->neighbours[i]->dead_end == 0)
		{
			if (room_in_bitfield(curr->dst->neighbours[i], visited) == 1)
			{
				if (queue_conflict(qr, curr->dst, curr->src,
				curr->dst->neighbours[i], map) == 1)
					add = 0;
			}
			if (add == 1)
			{
				if (create_new_path(&new, curr->path, curr->dst, map)
				== EXIT_FAILURE)
					return (EXIT_FAILURE);
				// if (has_other_options(dst, ))
				if (add_to_queue(qr, curr->dst,
				curr->dst->neighbours[i], new)
				== EXIT_FAILURE)
					return (EXIT_FAILURE);
				// if (curr->dst->neighbours[i] != map->start)
				add_to_bitfield(curr->dst->neighbours[i], visited);
				/* TEST */
				// if (curr->dst->neighbours[i] != map->start)
				// 	add_to_bitfield(curr->dst->neighbours[i], qr->visited);
			}
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
		{
			// printf("Set visited %s\n", iter->dst->name);
			add_to_bitfield(iter->dst, qr->visited);
		}
		iter = iter->next;
	}
	// printf("Done\n");
}

ssize_t		adjust_queue(t_qwrap *qr, t_map *map, size_t len)
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
	set_visited(qr, map);
	while (i < len)
	{
		if (add_nbs_to_queue(qr, curr, map, visited)
		== EXIT_FAILURE)
			return (EXIT_FAILURE);
		prev = curr;
		curr = curr->next;
		remove_queue_item(qr, prev);
		i++;
	}
	free (visited);
	return (EXIT_SUCCESS);
}
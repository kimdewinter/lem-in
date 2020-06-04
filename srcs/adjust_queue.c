/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   adjust_queue.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 12:35:53 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/04 16:34:32 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

/* Dst is the one that just got a path added to it, subpath is
the path that was added to it, src is where dst got it's path */
/* If one of it's neighbours IS start, that's the only one we add */

static size_t			already_in_queue(t_room *curr, uint64_t *visited)
{
	if ((visited[curr->room_i / BITFIELD_SIZE] &
	((BITFIELD_TYPE)1 << (63 - curr->room_i % BITFIELD_SIZE))) != 0)
		return (1);
	return (0);
}

static void			add_to_visited(t_room *curr, uint64_t *visited)
{
	visited[curr->room_i / BITFIELD_SIZE] |=
	((BITFIELD_TYPE)1 << (63 - curr->room_i % BITFIELD_SIZE));
}

void			remove_queue_item(t_qwrap *queue)
{
	t_list *last;

	last = ft_lstpop(queue->queue);
	if (last == queue->last)
		queue->last = NULL;
	if (last)
	{
		free (last->content);
		free (last);
	}
}

static size_t		add_nbs_to_queue(t_map *map, t_qwrap *queue, t_queue *curr,
size_t i)
{
	t_list	*new;
	int		new_conj;
	size_t	j;

	if (curr->dst == map->start)
		return (EXIT_SUCCESS);
	if (curr->dst->sps == 1)
		return (EXIT_SUCCESS);
	j = 0;
	new_conj = is_new_conj(curr->src, curr->dst, curr->dst->routes[i]);
	while (j < curr->dst->neighbours_len)
	{
		if (!(curr->dst->neighbours[j] == curr->src
		|| has_path_to_conj(curr->dst->neighbours[j],
		curr->dst->routes[i]->conj) == 1))
		{
			new = new_queue_item(curr->dst->routes[i], curr->dst->neighbours[j],
			curr->dst);
			((t_queue *)new->content)->new_conj = new_conj;
			if (new)
				ft_lstaddend_no_alloc(queue, new);
			else
				return (EXIT_FAILURE);
		}
		j++;
	}
	return (EXIT_SUCCESS);
}

static size_t			add_paths_to_nbs(t_qwrap *queue, t_map *map, t_queue *curr)
{
	size_t	i;

	i = 0;
	while (i < curr->dst->num_options)
	{
		if (add_nbs_to_queue(map, queue, curr, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

size_t			adjust_queue(t_map *map, t_qwrap *queue, size_t len)
{
	t_list		*iter;
	t_queue		*curr;
	uint64_t	*visited;
	size_t	i;

	if (bite_alloc(&visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	iter = (*queue->queue);
	if (iter)
		curr = (t_queue *)(iter->content);
	i = 0;
	while (i < len)
	{
		if (already_in_queue(curr->dst, visited) == 0)
		{
			add_to_visited(curr->dst, visited);
			if (add_paths_to_nbs(queue, map, curr) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		remove_queue_item(queue);
		iter = (*queue->queue);
		i++;
		if (iter)
			curr = (t_queue *)(iter->content);
	}
	free (visited);
	return (EXIT_SUCCESS);
}
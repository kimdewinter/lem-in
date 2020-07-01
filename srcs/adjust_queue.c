/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   adjust_queue.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 12:35:53 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/01 13:27:28 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		remove_queue_item(t_qwrap *qr, t_queue *item)
{
	t_queue *prev;
	t_queue *next;

	prev = item->prev;
	next = item->next;
	qr->items--;
	if (!prev)
		*(qr->queue) = next;
	else
		prev->next = next;
	if (next == NULL)
		qr->last = NULL;
	else
		next->prev = prev;
	free (item);
}

static int				new_path_is_improvement(t_subpath *old, t_subpath *new)
{
	if (new->segment_len < old->segment_len)
		return (1);
	return (0);
}


static int				check_queue_conflicts(t_qwrap *qr,
t_room *curr, t_room *src, t_subpath *pt)
{
	t_queue 	*iter;

	iter = qr->last;
	while (iter && iter->handled == 0)
	{
		if (iter->dst == curr)
		{
			if (iter->src != src)
				return (0);
			if (new_path_is_improvement(iter->path, pt) == 1)
			{
				remove_queue_item(qr, iter);
				return (0);
			}
		}
		iter = iter->prev;
	}
	return (0);
}


void				add_to_bitfield(t_room *curr, uint64_t *bitfield)
{
	bitfield[curr->room_i / BITFIELD_SIZE] |=
	((BITFIELD_TYPE)1 << (63 - curr->room_i % BITFIELD_SIZE));
}

int					room_in_bitfield(t_room *curr, BITFIELD_TYPE *bitfield)
{
	if ((bitfield[curr->room_i / BITFIELD_SIZE] &
	((BITFIELD_TYPE)1 << (63 - curr->room_i % BITFIELD_SIZE)))
	!= (BITFIELD_TYPE)0)
		return (1);
	return (0);
}

static size_t			add_to_queue(t_qwrap *qr, t_room *src, t_room *dst,
t_subpath *pt)
{
	t_queue *new;

	new = NULL;
	new = new_queue_item(pt, dst, src);
	if (new == NULL)
		return (EXIT_FAILURE);
	add_item_queue(&qr, new);
	return (EXIT_SUCCESS);
}

static int				adjust_viable_nbs(t_queue *curr, size_t i,
size_t round)
{
	/* Not viable if weight < nb weight OR it is bigger AND dst weight > rounds */
	if (!(curr->dst->neighbours[i]->nb->dead_end == 0
	&& curr->dst->neighbours[i]->available == 1
	&& (curr->dst->neighbours[i]->nb->weight == 0
	|| curr->dst->neighbours[i]->nb->weight > curr->dst->weight 
	|| (curr->dst->neighbours[i]->nb->weight < curr->dst->weight &&
	curr->dst->weight > round))))
	{
		print_paths(curr->dst->neighbours[i]->nb);
		printf("Not viable: %s weight %lu\n", curr->dst->neighbours[i]->nb->name,
		curr->dst->neighbours[i]->nb->weight);
		print_path(curr->path);
		curr->dst->viable_nbs--;
		return (0);
	}
	return (1);
}


int			check_length(t_subpath *new_path, t_room *curr)
{
	ssize_t	j;
	size_t	found;

	j = curr->num_options - 1;
	found = 0;
	printf("Check length dst: %s\n", curr->name);
	while (j >= 0)
	{
		if (curr->routes[j]->conj == new_path->conj)
		{
			found++;
			/* If the new path we're adding is longer than the one we currently
			have, don't add it UNLESS it's a straight path?? No because that
			would have arrived first */
			/* SHOULD THIS BE LEN??? */
			printf("seg len new %lu\nseg len old %lu\nlen old %lu\nlen new %lu",
			new_path->segment_len, curr->routes[j]->segment_len, new_path->len,
			curr->routes[j]->len);
			if ((new_path->segment_len + 1) > curr->routes[j]->segment_len)
				return (0);
			/* If it is equally long but the other path has no conflicts,
			don't add it */
			else if ((new_path->segment_len + 1) == curr->routes[j]->segment_len
			&& curr->routes[j]->sp == 1)
				return (0);
		}
		j--;
	}
	if (found == 0)
		return (0);
	return (1);
}

static size_t			is_viable_for_path(t_map *map, t_queue *item,
t_room *nb, t_subpath *path, size_t round)
{
	if (nb != item->src
	&& nb != path->conj
	&& (!(item->dst->sps == 1 && nb != map->start)))
	{
		printf("checking whether viable\n");
		/* This is true for every room that hasn't gotten a path yet,
		start being the exception */
		if (nb->weight == 0)
			return (1);
		else if (nb->weight > item->dst->weight)
		{
			/* The nb is further away then the dst, so we do our checks
			(has path etc) 8 to 6 test compl 1 and 8 to 4 */
			if (has_path_to_conj(nb, path->conj) == 1)
			{
				printf("Has path to conj\n");
				if (check_length(path, nb) == 1)
					return (1);
				return (0);
			}
			else
				return (1);
		}
		else if (nb->weight < item->dst->weight &&
		item->dst->weight > round)
		{
			/* The dst in question has a single path, we should check whether
			to add it to this nb (has path etc) 6 to 5 and 4 to 5 */
			if (has_path_to_conj(nb, path->conj) == 1)
				return (0);
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

static size_t			add_nbs_to_queue(t_qwrap *qr, t_queue *curr, t_map *map,
BITFIELD_TYPE **already_in_queue)
{
	size_t		i;
	size_t		j;
	int			in_queue;
	int			viable;
	size_t		added;

	i = 0;
	in_queue = 0;
	viable = 0;
	curr->dst->viable_nbs = curr->dst->neighbours_len;
	while (i < curr->dst->neighbours_len)
	{
		in_queue = 0;
		j = 0;
		added = 0;
		printf("\n\nNB %s\n", curr->dst->neighbours[i]->nb->name);
		viable = adjust_viable_nbs(curr, i, qr->round);
		printf("Viable %d\n", viable);
		while (j < curr->dst->num_options)
		{
			if (curr->dst->routes[j]->added_this_turn == 1)
			{
				/*See if this nb is a candidate */
				printf("Curr path\n");
				print_path(curr->dst->routes[j]);
				printf("---->");
				if (curr->dst == map->start)
					return (EXIT_SUCCESS);
				/* Solves path conflicts */
				if (viable == 1 && is_viable_for_path(map,
				curr, curr->dst->neighbours[i]->nb, curr->dst->routes[j],
				qr->round) == 1)
				{
					printf("Is viable for path\n");
					in_queue = room_in_bitfield(curr->dst->neighbours[i]->nb,
					*already_in_queue);
					/* Solves queue conflicts */
					if (in_queue == 0 || check_queue_conflicts(qr, curr->dst->neighbours[i]->nb,
					curr->dst, curr->dst->routes[j]) == 0)
					{
						printf("Will be added\n");
						added++;
						// if ((curr->dst->neighbours[i]->nb->weight == 0
						// || curr->dst->neighbours[i]->nb->weight > 
						// curr->dst->weight) && curr->dst->neighbours[i]->nb != map->start)
						// 	curr->dst->neighbours[i]->nb->weight =
						// 	curr->dst->weight + 1;
						if (add_to_queue(qr, curr->dst,
						curr->dst->neighbours[i]->nb, curr->dst->routes[j]) == EXIT_FAILURE)
							return (EXIT_FAILURE);
						add_to_bitfield(curr->dst->neighbours[i]->nb,
						*already_in_queue);
					}
				}
			}
			j++;
		}
		if (curr->dst->neighbours[i]->nb != map->start
		&& curr->dst->weight <= qr->round)
		{
			curr->dst->neighbours[i]->available = 0;
		}
		if (added > 1 && curr->dst->neighbours[i]->nb->checked == 0)
		{
			curr->dst->neighbours[i]->nb->is_conj = 1;
			curr->dst->neighbours[i]->nb->checked = 1;
		}
		i++;
	}
	if (curr->dst->viable_nbs == 1 && curr->dst->num_options == 0)
		curr->dst->is_conj = 0;
	curr->dst->checked = 1;
	return (EXIT_SUCCESS);
}

static void	set_weights(t_queue **queue, t_map *map)
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

size_t		adjust_queue(t_qwrap *qr, t_map *map)
{
	t_queue			*curr;
	size_t			i;
	size_t			len;
	BITFIELD_TYPE	*visited;
	BITFIELD_TYPE	*already_in_queue;

	printf("ADJUST QUEUE\n");
	if (bite_alloc(&visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (bite_alloc(&already_in_queue, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	curr = *(qr->queue);
	i = 0;
	len = qr->items;
	qr->round++;
	while (i < len)
	{
		if (room_in_bitfield(curr->dst, visited) == 0)
		{
			if (add_nbs_to_queue(qr, curr, map, &already_in_queue) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			add_to_bitfield(curr->dst, visited);
		}
		remove_queue_item(qr, curr);
		i++;
		curr = curr->next;
	}
	// if (qr->round == 5)
	// {
	// 	print_queue(qr);
	// 	debug (map);
	// 	exit (0);
	// }
	set_weights(qr->queue, map);
	return (EXIT_SUCCESS);
}
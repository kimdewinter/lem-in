/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_adjust.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 12:35:53 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/21 21:03:50 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t			add_nb_to_queue(t_qwrap *qr, t_room *nb, t_map *map)
{
	t_room		*dst;
	t_subpath	*new;
	int			valid;
	int			res;

	new = NULL;
	dst = NULL;
	res = 0;
	valid = find_next_dst(nb, *(qr->queue), &new, &dst, map);
	if (valid == 0)
		return (EXIT_SUCCESS);
	if (valid == -1)
		return (EXIT_FAILURE);
	// printf("REAL DST %s\nPATH\n", dst->name);
	// print_path(new);
	// printf("\n\nADD TO QUEUE\n");
	if (room_in_bitfield(dst, (*qr->queue)->dst->bitconj) == 1)
	{
		/* 1 means should be added */
		res = solve_path_conflict(dst, new);
		if (res == -1)
			delete_path(&new);
		if (res == -1 || res == 0)
			return (EXIT_SUCCESS);
	}
	if (room_in_bitfield(dst, qr->visited) == 1)
	{
		if (solve_queue_conflict(qr, new, dst) == 0)
		{
			delete_path(&new);
			return (EXIT_SUCCESS);
		}
	}
	if (add_to_queue(qr, (*qr->queue)->dst, dst, new) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static ssize_t			add_nbs_to_queue(t_qwrap *qr, t_queue *curr, t_map *map)
{
	size_t		i;

	i = 0;
	// printf("\n\nCURR %s\n", curr->dst->name);
	if (curr->dst == map->start)
		return (EXIT_SUCCESS);
	while (i < curr->dst->neighbours_len)
	{
		// printf("neighbour %s\n", curr->dst->neighbours[i]->name);
		if (curr->dst->neighbours[i]->dead_end == 0
		&& room_in_bitfield(curr->dst->neighbours[i], curr->dst->unavailable)
		== 0)
		{
			// printf("Viable\n");
			add_nb_to_queue(qr, curr->dst->neighbours[i], map);
		}
//				&& ft_strcmp(curr->src->name, "15") == 0
		// if (ft_strcmp(curr->dst->name, "12") == 0 
		// && ft_strcmp(curr->dst->neighbours[i]->name, "13") == 0
		// && ft_strcmp(curr->src->name, "7") == 0)
		// {
		// 	printf("Oki\n");
		// 	// print_paths(curr->dst->neighbours[i]);
		// 	exit (0);
		// }
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

// ssize_t		add_to_visited(t_qwrap *qr, t_map *map)
// {
// 	t_queue *tmp;

// 	tmp = *(qr->queue);
// 	while (tmp)
// 	{
// 		add_to_bitfield(tmp->src, qr->visited);
// 		tmp = tmp->next;
// 	}
// }

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
	if (qr->round == 3)
	{
		// printf("AFTER\n");
		// print_queue(qr);
		exit (0);
	}
	return (EXIT_SUCCESS);
}

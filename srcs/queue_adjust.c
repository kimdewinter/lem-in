/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_adjust.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 12:35:53 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/20 20:52:41 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t			add_nbs_to_queue(t_qwrap *qr, t_queue *curr, t_map *map)
{
	size_t		i;

	i = 0;
	// printf("\n\nCURR %s\n", curr->dst->name);
	if (curr->dst == map->start)
	{
		// printf("map start\n");
		return (EXIT_SUCCESS);
	}
	while (i < curr->dst->neighbours_len)
	{
		// printf("neighbour %s dead end %d\n", curr->dst->neighbours[i]->name,
		// curr->dst->neighbours[i]->dead_end);
		if (curr->dst->neighbours[i]->dead_end == 0)
		{
			if (add_nb_to_queue(map, curr, curr->dst->neighbours[i], qr)
			== EXIT_FAILURE)
				return (EXIT_FAILURE);
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
	printf("LEN QUEUE %lu\n", len);
	// if (len == 2)
	// {
	// 	printf("Map start %s Map end %s\n", map->start->name, map->end->name);
	// 	print_queue(qr);
	// 	exit (0);
	// }
	while (i < len)
	{
		// printf("%lu\n", i);
		if (add_nbs_to_queue(qr, curr, map)
		== EXIT_FAILURE)
			return (EXIT_FAILURE);
		prev = curr;
		curr = curr->next;
		remove_queue_item(qr, prev);
		i++;
	}
	// printf("AFTER ADJUST\n");
	// print_queue(qr);
	// if (qr->round == 3)
	// {
	// 	printf("AFTER\n");
	// 	print_queue(qr);
	// 	exit (0);
	// }
	return (EXIT_SUCCESS);
}

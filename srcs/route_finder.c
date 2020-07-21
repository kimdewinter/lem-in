/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 14:33:23 by kim           #+#    #+#                 */
/*   Updated: 2020/07/21 19:11:41 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t				add_path_to_dst(t_qwrap *qr, t_queue *curr,
t_map *map)
{
	t_subpath	*new;

	new = NULL;
	if (curr->path == NULL && qr->round == 2)
	{
		if (create_new_path(&new, NULL, map->end, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (add_path_to_room(curr, map, &new) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		curr->path = new;
	}
	else
	{
		// if (create_new_path(&new, NULL, curr->dst, map) == EXIT_FAILURE)
		// 	return (EXIT_FAILURE);
		if (add_path_to_room(curr, map, &(curr->path)) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static ssize_t			execute_queue(t_qwrap *qr, t_map *map)
{
	t_queue	*iter;

	iter = *(qr->queue);
	while (iter != NULL)
	{
		iter->handled = 1;
		if (add_path_to_dst(qr, iter, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		iter = iter->next;
		if (iter == NULL)
		{
			// printf("Before adjust queue\n");
			if (adjust_queue(qr, map, qr->items) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			iter = *(qr->queue);
			// printf("After adjust queue %p\n", iter);
		}
	}
	// printf("Done\n");
	free (qr->in_queue);
	free (qr->queue);
	free (qr);
	debug (map);
	// print_paths(map->start);
	exit (0);
	return (EXIT_SUCCESS);
}

ssize_t			find_routes(t_map *map)
{
	t_qwrap		*queue;

	if (setup_queue(&queue, map) == EXIT_SUCCESS &&
		execute_queue(queue, map) == EXIT_SUCCESS &&
		assemble_all_routes(map) == EXIT_SUCCESS)
	{
		debug(map);
		printf("paths found: %lu", map->num_routes);
		print_routes(map);
		exit (0);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

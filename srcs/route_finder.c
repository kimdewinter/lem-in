/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 14:33:23 by kim           #+#    #+#                 */
/*   Updated: 2020/07/26 21:57:50 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t			execute_queue(t_qwrap *qr, t_map *map)
{
	t_queue	*iter;

	iter = *(qr->queue);
	while (iter)
	{
		iter->handled = 1;
		if (add_path_to_room(iter->dst, map, &(iter->path))
		== EXIT_FAILURE)
			return (EXIT_FAILURE);
		iter = iter->next;
		if (iter == NULL)
		{
			// printf("BEFORE ADJUST QUEUE\n");
			// print_queue(qr);
			if (adjust_queue(qr, map, qr->items) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			// printf("AFTER ADJUST QUEUE\n");
			// print_queue(qr);
			iter = *(qr->queue);
		}
	}
	free (qr->queue);
	free (qr->visited);
	free (qr);
	return (EXIT_SUCCESS);
}

ssize_t			find_routes(t_map *map)
{
	t_qwrap		*queue;
	size_t		i;

	i = 0;
	while (i < map->end->neighbours_len)
	{
		if (setup_queue(&queue, map->end->neighbours[i], map) == EXIT_FAILURE
		|| execute_queue(queue, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	assemble_all_routes(map);
	print_routes(map);
	printf("NUM PATHS %lu\n", map->num_routes);
	exit (0);
	// size_t	res;
	// max_parallels(&res, map);
	// printf("paths: %lu end nodes: %lu\n", map->start->num_options, map->end->neighbours_len);
	// printf("max parallels %lu\n", res);
	// for (size_t	i = 0; i < map->start->neighbours_len; i++)
	// {
	// 	printf("options per start nb: %lu\n", map->start->neighbours[i]->num_options);
	// }
	// print_paths(map->start);
	// exit (0);
	// size_t result;

	// result = 0;
	// if (max_parallels(&result, map) == EXIT_FAILURE)
	// 	printf("Went wrong");
	// printf("max parallels %lu\n", result);
	// exit (0);
	// printf("Paths found %ld\n", map->start->num_options);
	// exit (0);
	return (EXIT_SUCCESS);
}

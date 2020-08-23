/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 14:33:23 by kim           #+#    #+#                 */
/*   Updated: 2020/08/23 19:19:33 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			reset_dists(t_table *rooms, int to_start, int to_end)
{
	size_t	i;

	i = 0;
	while (i < rooms->size)
	{
		if (rooms->entries[i] != NULL)
		{
			if (to_start == 1)
				((t_room *)rooms->entries[i]->val)->dist_to_start = -1;
			if (to_end == 1)
				((t_room *)rooms->entries[i]->val)->dist_to_end = -1;
		}
		i++;
	}
}

ssize_t			find_routes(t_map *map)
{
		// printf("start nbs %lu end nbs %lu\n", map->start->neighbours_len, map->end->neighbours_len);

	t_best	candidate;
	ssize_t	blocks_found;

	// print_map(map);
	// exit (0);
	blocks_found = EXIT_SUCCESS;
	while (blocks_found == EXIT_SUCCESS)
	{
		if (map->start == NULL)
			return (EXIT_FAILURE);
		// if (traverse_bf(map->end, LVL_GRPH_E2S, map) == EXIT_FAILURE)//step 1: create level graph from end to start
		// 	return (EXIT_FAILURE);
		/* Find distances to end */
		if (set_weights(map, -1, NULL) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		// print_map(map);
		// exit (0);
		// printf("After set weights\n");
		if (find_parallel_routes(&candidate, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (candidate.used == 0)
			return (EXIT_SUCCESS);
		// print_best(&candidate);
		// print_in_paths(candidate.in_paths, map);

		// exit (0);
		// if (find_routes_df(&candidate, map) == EXIT_FAILURE)//step 2: DFS for valid parallel routes
		// 	return (EXIT_FAILURE);
		if (set_weights(map, 1, NULL) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		// print_map(map);
		// if (traverse_bf(map->start, LVL_GRPH_S2E, map) == EXIT_FAILURE)//step 3: level graph start to end
		// 	return (EXIT_FAILURE);
		// print_best(&candidate);
		blocks_found = remove_blockage(&candidate, map);
		// exit (0);
		// if (blocks_found == EXIT_NO_BLOCKS)
		// 	printf("NO BLOCKS FOUND\n");
		// exit (0);
		if (blocks_found == EXIT_FAILURE)
			return (EXIT_FAILURE);
		compare_candidate_best(map, &candidate);
		reset_dists(map->rooms, 1, 1);
		// printf("Current best solution:\nturns: %lu\nants: %ld\n", map->solution.turns, map->antmount);
		// print_best(&map->solution);
	}
	// exit (0);
	// printf("start nbs %lu end nbs %lu\n", map->start->neighbours_len, map->end->neighbours_len);
	// printf("COST: %lu\n", map->solution.turns);
	// exit (0);
	return (EXIT_SUCCESS);
	// PLACEHOLDER: check whether candidate is now better than the previous map->solution, replace if needed
	// print_rooms(map->rooms);
	// exit (EXIT_SUCCESS);
	// return (EXIT_SUCCESS);
}

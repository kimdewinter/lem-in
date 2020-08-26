/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 14:33:23 by kim           #+#    #+#                 */
/*   Updated: 2020/08/26 11:15:17 by lravier       ########   odam.nl         */
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

static ssize_t	free_and_ret(t_best *candidate, ssize_t ret)
{
	delete_solution(candidate);
	return (ret);
}

static ssize_t	handle_no_paths_found(t_best *candidate)
{
	if (candidate->combi == NULL)
		return (ft_error("Error: no valid path found\n", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

ssize_t			find_routes(t_map *map)
{
	t_best	candidate;
	ssize_t	blocks_found;

	blocks_found = EXIT_SUCCESS;
	while (blocks_found == EXIT_SUCCESS)
	{
		if (set_weights(map, -1, NULL) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		setup_candidate(&candidate);
		if (find_parallel_routes(&candidate, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (candidate.used == 0)
			return (handle_no_paths_found(&candidate));
		if (set_weights(map, 1, NULL) == EXIT_FAILURE)
			free_and_ret(&candidate, EXIT_FAILURE);
		blocks_found = remove_blockage(&candidate, map);
		if (blocks_found == EXIT_FAILURE)
			free_and_ret(&candidate, EXIT_FAILURE);
		compare_candidate_best(map, &candidate);
		reset_dists(map->rooms, 1, 1);
	}
	return (EXIT_SUCCESS);
}

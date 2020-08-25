/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 14:33:23 by kim           #+#    #+#                 */
/*   Updated: 2020/08/25 15:15:03 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			reset_dist_to_x(t_table *rooms)
{
	size_t	i;

	i = 0;
	while (i < rooms->size)
	{
		if (rooms->entries[i] != NULL)
		{
			((t_room *)rooms->entries[i]->val)->dist_to_start = -1;
			((t_room *)rooms->entries[i]->val)->dist_to_end = -1;
		}
		i++;
	}
}

ssize_t			find_routes(t_map *map)
{
	t_best	candidate;
	ssize_t	blocks_found;

	blocks_found = EXIT_SUCCESS;
	while (blocks_found == EXIT_SUCCESS)
	{
		if (map->start == NULL)
			return (EXIT_FAILURE);
		if (traverse_bf(map->end, NULL, LVL_GRPH_E2S, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		setup_candidate(&candidate);
		if (find_parallel_routes(&candidate, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (candidate.used == 0)
			return (EXIT_SUCCESS);
		if (traverse_bf(map->start, NULL, LVL_GRPH_S2E, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		blocks_found = remove_blockage(&candidate, map);
		if (blocks_found == EXIT_FAILURE)
			return (EXIT_FAILURE);
		compare_candidate_best(map, &candidate);
		reset_dist_to_x(map->rooms);
	}
	return (EXIT_SUCCESS);
}

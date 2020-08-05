/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   df_routefinder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 15:49:14 by kim           #+#    #+#                 */
/*   Updated: 2020/08/05 15:40:30 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t	find_shortest_dist_to_end(t_find_routes_df_wrap *wrap,
												const t_map *map)
{
	size_t	i;

	wrap->shortest_dist_to_end = NULL;
	i = 0;
	while (i < map->start->neighbours_len)
	{
		if (wrap->shortest_dist_to_end == NULL ||
			map->start->neighbours[i]->dist_to_end <
			wrap->shortest_dist_to_end->dist_to_end)
		{
			if (room_in_bitfield(map->start->neighbours[i], wrap->visited) == 0)
				wrap->shortest_dist_to_end = map->start->neighbours[i];
		}
	}
	if (wrap->shortest_dist_to_end == NULL)
		return (0);
	else
		return (1);
}
/*
** return of 0 means no valid shortest-dist-to-end start nb was found
*/

static ssize_t	setup_best(t_best *best, const t_map *map)
{
	size_t	i;

	best->len = (map->start->neighbours_len < map->end->neighbours_len)
		? map->start->neighbours_len : map->end->neighbours_len;
	best->combi =
		(t_route **)malloc(sizeof(t_route *) * best->len);
	if (best->combi == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < best->len)
	{
		best->combi[i] = NULL;
		i++;
	}
	best->used = 0;
	best->turns = 0;
	return (EXIT_SUCCESS);
}

ssize_t			find_routes_df(t_map *map)
{
	t_find_routes_df_wrap	wrap;

	if (map->solution.combi == NULL)
		if (setup_best(&map->solution, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (setup_best(&wrap.candidate_best, map) == EXIT_FAILURE ||
		bite_alloc(&wrap.visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (find_shortest_dist_to_end(&wrap, map) == 1)
	{
		bite_add_room_to_bitfield(
			wrap.visited, wrap.shortest_dist_to_end->bitroom, map);//to make sure a start nb that has no valid route to end is not repeatedly visited
		if (init_find_route_df(wrap.shortest_dist_to_end, &wrap, map) ==
			EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
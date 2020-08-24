/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_parallel_routes.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 16:41:48 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/24 16:36:38 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	commit_route(t_best *candidate, t_route *route, t_map *map)
{
	int		first;

	first = 0;
	if (candidate->combi == NULL)
	{
		if (init_combi(map, &candidate) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		first = 1;
	}
	if (first == 0)
	{
		candidate->prev_turns = candidate->turns;
		if (is_improvement(candidate, route, map) == 0)
			return (PATHS_DONE);
	}
	if (init_route(candidate, map, route) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	set_route(candidate, route, map);
	if (candidate->used == (size_t)map->antmount ||
	candidate->used == map->start->neighbours_len ||
	candidate->used == map->end->neighbours_len)
		return (PATHS_DONE);
	return (EXIT_SUCCESS);
}

static int		find_route(t_room *start, BITFIELD_TYPE *visited,
t_route *route, t_map *map)
{
	ssize_t	i;
	size_t	tried;
	size_t	found;

	i = 0;
	tried = 0;
	found = 0;
	if (start == map->end)
		return (1);
	bite_add_room_to_bitfield(start, visited);
	while (found == 0 && tried < start->neighbours_len)
	{
		find_best_option(start, visited, &i);
		tried++;
		if (i == -1)
			return (0);
		route->route[route->used] = start->neighbours[i];
		route->used++;
		found = find_route(start->neighbours[i], visited, route, map);
		if (found == 1)
			return (1);
		route->used--;
		route->route[route->used] = NULL;
	}
	return (0);
}

static ssize_t	handle_route_found(t_best *candidate, t_route *route,
t_map *map)
{
	int	ret;

	ret = commit_route(candidate, route, map);
	if (ret == EXIT_FAILURE || ret == PATHS_DONE)
		return (ret);
	reset_dists(map->rooms, 0, 1);
	set_weights(map, -1, candidate->in_paths);
	return (EXIT_SUCCESS);
}

ssize_t			find_parallel_routes(t_best *candidate, t_map *map)
{
	ssize_t			i;
	t_route			route;
	ssize_t			ret;
	BITFIELD_TYPE	*visited;

	i = 0;
	ret = 0;
	if (setup_routefinder(&visited, &route, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (i != -1)
	{
		find_best_option(map->start, visited, &i);
		if (i == -1)
			return (free_find_parallel(&visited, &route, EXIT_SUCCESS));
		route.route[route.used] = map->start->neighbours[i];
		route.used++;
		if (find_route(map->start->neighbours[i], visited, &route, map) == 1)
		{
			ret = handle_route_found(candidate, &route, map);
			if (ret == EXIT_FAILURE || ret == PATHS_DONE)
				return (free_find_parallel(&visited, &route, ret));
		}
		reset_route(&route);
	}
	return (free_find_parallel(&visited, &route, EXIT_SUCCESS));
}

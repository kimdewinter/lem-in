/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder_utils_2.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 13:52:42 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/24 14:46:05 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int				is_improvement(t_best *best, t_route *add, t_map *map)
{
	size_t	new_cost;

	new_cost = calc_cost_add_route(best, add, map);
	if (new_cost >= best->turns)
		return (0);
	return (1);
}

void			setup_candidate(t_best *candidate)
{
	candidate->combi = NULL;
	candidate->in_paths = NULL;
	candidate->len = 0;
	candidate->prev_turns = 0;
	candidate->turns = 0;
	candidate->used = 0;
}

ssize_t		free_find_parallel(BITFIELD_TYPE **visited, t_route *route,
ssize_t	ret)
{
	free(*visited);
	*visited = NULL;
	free(route->route);
	route->route = NULL;
	return (ret);
}


ssize_t		setup_routefinder(BITFIELD_TYPE **visited, t_route *route,
t_map *map)
{
	if (bite_alloc(visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (setup_route(route, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	bite_add_room_to_bitfield(map->start, *visited);
	return (EXIT_SUCCESS);
}
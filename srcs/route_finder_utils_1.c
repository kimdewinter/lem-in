/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder_utils_1.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 13:49:38 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/24 14:18:49 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t			setup_route(t_route *route, t_map *map)
{
	route->ants = 0;
	route->bitroute = NULL;
	route->len = map->rooms->count;
	route->used = 0;
	route->route = (t_room **)malloc(sizeof(t_room *) * map->rooms->count);
	if (route->route == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void			reset_route(t_route *route)
{
	size_t	i;

	i = 0;
	while (i < route->used)
	{
		route->route[i] = NULL;
		i++;
	}
	route->used = 0;
}

ssize_t			init_combi(t_map *map, t_best **candidate)
{
	size_t	num_routes;

	if (map->end->neighbours_len < map->start->neighbours_len)
		num_routes = map->end->neighbours_len;
	else
		num_routes = map->start->neighbours_len;
	(*candidate)->combi = (t_route **)malloc(sizeof(t_route *) * num_routes);
	if ((*candidate)->combi == NULL)
		return (EXIT_FAILURE);
	if (bite_alloc(&((*candidate)->in_paths), map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	(*candidate)->len = num_routes;
	return (EXIT_SUCCESS);
}

ssize_t			init_route(t_best *candidate, t_map *map, t_route *route)
{
	candidate->combi[candidate->used] = (t_route *)malloc(sizeof(t_route));
	if (candidate->combi[candidate->used] == NULL)
		return (EXIT_FAILURE);
	candidate->combi[candidate->used]->route =
	(t_room **)malloc(sizeof(t_room *) * route->used);
	if (candidate->combi[candidate->used]->route == NULL)
		return (EXIT_FAILURE);
	if (bite_alloc(&candidate->combi[candidate->used]->bitroute, map)
	== EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);	
}

void			set_route(t_best *candidate, t_route *route, t_map *map)
{
	size_t	i;

	i = 0;
	while (i < route->used)
	{
		candidate->combi[candidate->used]->route[i] = route->route[i];
		if (route->route[i] != map->end)
		{
			bite_add_room_to_bitfield(route->route[i],
			candidate->combi[candidate->used]->bitroute);
			bite_add_room_to_bitfield(route->route[i], candidate->in_paths);
		}
		i++;
	}
	candidate->combi[candidate->used]->len = route->len;
	candidate->combi[candidate->used]->used = route->used;
	candidate->used++;
	candidate->turns = calc_cost(map->antmount, candidate);
}

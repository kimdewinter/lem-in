/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_parallel_routes.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 16:41:48 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/23 20:36:24 by lravier       ########   odam.nl         */
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

static ssize_t	init_combi(t_map *map, t_best **candidate)
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

static ssize_t	init_route(t_best *candidate, t_map *map, t_route *route)
{
	// printf("INIT ROUTE\n");
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

static void	set_route(t_best *candidate, t_route *route, t_map *map)
{
	size_t	i;

	i = 0;
	// printf("SET ROUTE\n");
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

static int		is_improvement(t_best *best, t_route *add, t_map *map)
{
	size_t	new_cost;

	// printf("CHECK IF IMPROVEMENT\n");
	new_cost = calc_cost_add_route(best, add, map);
	if (new_cost >= best->turns)
		return (0);
	return (1);
}

static ssize_t	commit_route(t_best *candidate, t_route *route, t_map *map)
{
	int		first;

	first = 0;
	// printf("COMMIT ROUTE\n");
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

static void		find_best_option(t_room *start, BITFIELD_TYPE *visited, ssize_t *i)
{
	ssize_t	best;
	size_t	j;

	*i = 0;
	j = *i;
	best = -1;
	while (j < start->neighbours_len)
	{
		if (room_in_bitfield(start->neighbours[j], visited) == 0
		&& start->neighbours[j]->dist_to_end >= 0)
		{
			if (best == -1)
				best = j;
			else
			{
				if (start->neighbours[j]->dist_to_end
				< start->neighbours[best]->dist_to_end)
					best = j;
				if (start->spe == 1
				&& start->neighbours[j] == start->spe_start
				&& start->neighbours[j]->dist_to_end ==
				start->neighbours[best]->dist_to_end)
					best = j;
			}
			/* Make sure to choose the spe option if it exist and
			it's len is not longer than the current best */
		}
		j++;
	}
	*i = best;
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

void			setup_candidate(t_best *candidate)
{
	candidate->combi = NULL;
	candidate->in_paths = NULL;
	candidate->len = 0;
	candidate->prev_turns = 0;
	candidate->turns = 0;
	candidate->used = 0;
}

ssize_t			find_parallel_routes(t_best *candidate, t_map *map)
{
	ssize_t			i;
	size_t			tried;
	size_t			found;
	t_route			route;
	size_t			ret;
	BITFIELD_TYPE	*visited;

	i = 0;
	tried = 0;
	found = 0;
	ret = 0;
	setup_candidate(candidate);
	if (bite_alloc(&visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (setup_route(&route, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	bite_add_room_to_bitfield(map->start, visited);
	while (tried < map->start->neighbours_len)
	{
		find_best_option(map->start, visited, &i);
		tried++;
		if (i == -1)
			return (EXIT_SUCCESS);
		route.route[route.used] = map->start->neighbours[i];
		route.used++;
		found = find_route(map->start->neighbours[i], visited, &route, map);
		if (found == 1)
		{
			found = 0;
			ret = commit_route(candidate, &route, map);
			if (ret == EXIT_FAILURE || ret == PATHS_DONE)
			{
				free(route.route);
				free(visited);
				return (ret);
			}
			reset_dists(map->rooms, 0, 1);
			set_weights(map, -1, candidate->in_paths);
		}
		reset_route(&route);
	}
	free (visited);
	free (route.route);
	return (EXIT_SUCCESS);
}
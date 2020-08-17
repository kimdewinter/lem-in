/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_parallel_routes.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 16:41:48 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/17 21:14:21 by lravier       ########   odam.nl         */
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

static ssize_t	commit_route(t_best *candidate, t_route *route, t_map *map)
{
	size_t	i;
	size_t	num_routes;

	i = 0;
	num_routes = 0;
	if (candidate->combi == NULL)
	{
		printf("Init candidate\n\n");
		if (map->end->neighbours_len < map->start->neighbours_len)
			num_routes = map->end->neighbours_len;
		else
			num_routes = map->start->neighbours_len;
		candidate->combi = (t_route **)malloc(sizeof(t_route *) * num_routes);
		printf("Num routes %lu\n", num_routes);
		if (candidate->combi == NULL)
			return (EXIT_FAILURE);
		candidate->len = num_routes;
	}
	candidate->combi[candidate->used] = (t_route *)malloc(sizeof(t_route));
	if (candidate->combi[candidate->used] == NULL)
		return (EXIT_FAILURE);
	candidate->combi[candidate->used]->route = (t_room **)malloc(sizeof(t_room *) *
	route->used);
	if (candidate->combi[candidate->used]->route == NULL)
		return (EXIT_FAILURE);
	if (bite_alloc(&candidate->combi[candidate->used]->bitroute, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (i < route->used)
	{
		if (route->route[i] != map->end)
			bite_add_room_to_bitfield(route->route[i], candidate->combi[candidate->used]->bitroute);
		i++;
	}
	i = 0;
	// printf("Route used %lu Candidate used %lu\n", route->used, candidate->used);
	while (i < route->used)
	{
		// printf("In while %lu\n", i);
		candidate->combi[candidate->used]->route[i] = route->route[i];
		// printf("%s\n", candidate->combi[candidate->used]->route[i]->name);
		i++;
	}
	candidate->combi[candidate->used]->len = route->len;
	candidate->combi[candidate->used]->used = route->used;
	// printf("PRINT ROUTE\n\n");
	// printf("Used %lu\n", candidate->combi[candidate->used]->used);
	// print_troute(candidate->combi[candidate->used]);
	candidate->used++;
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
		if (room_in_bitfield(start->neighbours[j], visited) == 0)
		{
			if (best == -1)
				best = j;
			else
			{
				if (start->neighbours[j]->dist_to_end
				< start->neighbours[best]->dist_to_end)
					best = j;
			}
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
		// if (i != -1)
		// 	printf("Best option %s\n", start->neighbours[i]->name);
		tried++;
		if (i == -1)
			return (0);
		route->route[route->used] = start->neighbours[i];
		route->used++;
		found = find_route(start->neighbours[i], visited, route, map);
		if (found == 1)
			return (1);
		route->route[route->used] = NULL;
		route->used--;
	}
	return (0);
}

void			setup_candidate(t_best *candidate)
{
	candidate->combi = NULL;
	candidate->len = 0;
	candidate->turns = 0;
	candidate->used = 0;
}

ssize_t			find_parallel_routes(t_best *candidate, t_map *map)
{
	ssize_t			i;
	size_t			tried;
	size_t			found;
	t_route			route;
	BITFIELD_TYPE	*visited;

	i = 0;
	tried = 0;
	found = 0;
	// printf("Before find parallel route\n");
	// print_map(map);
	setup_candidate(candidate);
	if (bite_alloc(&visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (setup_route(&route, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	bite_add_room_to_bitfield(map->start, visited);
	while (tried < map->start->neighbours_len)
	{
		find_best_option(map->start, visited, &i);
		if (i != -1)
			printf("Best option %s\n", map->start->neighbours[i]->name);
		tried++;
		if (i == -1)
			return (EXIT_SUCCESS);
		route.route[route.used] = map->start->neighbours[i];
		route.used++;
		found = find_route(map->start->neighbours[i], visited, &route, map);
		if (found == 1)
		{
			printf("Found way to end\n");
			found = 0;
			// printf("Commit\n");
			if (commit_route(candidate, &route, map) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		reset_route(&route);
	}
	free (visited);
	return (EXIT_SUCCESS);
}
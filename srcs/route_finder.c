/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 14:33:23 by kim           #+#    #+#                 */
/*   Updated: 2020/06/04 14:00:49 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

size_t		is_in_path(t_map *map, size_t i, t_room *room)
{
	t_route			*route;

	route = map->routes[i];
	if (route->bitroute[room->room_i / BITFIELD_SIZE] &
	room->bitroom[room->room_i / BITFIELD_SIZE])
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

size_t		duplicate_route(t_map *map, size_t i)
{
	t_route	*new;
	t_route *curr;

	curr = map->routes[i];
	new = setup_route(curr->size);
	if (new)
	{
		if (copy_route(&curr, &new, map) == EXIT_SUCCESS)
		{
			if (add_route(map, new) == EXIT_SUCCESS)
				return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

size_t		add_neighbour_new_path(t_room *last, t_map *map,
									size_t j, size_t i)
{
	if (duplicate_route(map, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (add_to_route(&map->routes[map->num_routes - 1],
	last->neighbours[j], map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (last->neighbours[j] == map->start)
		map->routes[map->num_routes - 1]->solved = 1;
	else
		map->active_routes += 1;
	return (EXIT_SUCCESS);
}

size_t		add_neighbour_orig_path(t_room *add_to_orig,
									t_map *map, size_t i)
{
	if (add_to_route(&map->routes[i], add_to_orig, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (add_to_orig == map->start)
	{
		map->active_routes -= 1;
		map->routes[i]->solved = 1;
	}
	return (EXIT_SUCCESS);
}

void		kill_path(t_map *map, size_t i)
{
	map->routes[i]->dead = 1;
	map->active_routes -= 1;	
}

size_t		add_path_to_neighbours(t_map *map, size_t i, size_t *found,
									t_room *last)
{
	size_t	j;
	size_t	splits;
	t_room	*add_to_orig;

	j = 0;
	splits = 0;
	while (j < last->neighbours_len)
	{
		if (is_in_path(map, i, last->neighbours[j]) == EXIT_FAILURE)
		{
			*found = 1;
			if (splits != 0)
			{
				if (add_neighbour_new_path(last, map, j, i) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else
				add_to_orig = last->neighbours[j];
			splits++;
		}
		j++;
	}
	if (*found && add_neighbour_orig_path(add_to_orig, map, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

size_t		create_paths(t_map *map)
{
	size_t	i;
	size_t	found;
	t_room	*last;

	map->active_routes = 1;
	while (map->active_routes != 0)
	{
		found = 0;
		i = 0;
		while (i < map->num_routes && (map->routes[i]->dead == 1 ||
		map->routes[i]->solved == 1))
			i++;
		last = map->routes[i]->route[map->routes[i]->len - 1];
		if (add_path_to_neighbours(map, i, &found, last) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (found == 0)
			kill_path(map, i);
	}
	return (EXIT_SUCCESS);
}

size_t		find_routes(t_map *map)
{
	if (init_routes(map) == EXIT_SUCCESS)
	{
		create_paths(map);
		print_routes(map);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:34:22 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/04 13:56:47 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void		handle_error(t_map *map)
{
	size_t i;

	i = 0;
	if (map->routes)
	{
		while (i < map->num_routes)
		{
			if (map->routes[i])
				free (map->routes[i]);
			i++;
		}
		free (map->routes);
	}
}

t_route		*setup_route(size_t size)
{
	t_route *route;

	route = (t_route *)malloc(sizeof(t_route));
	if (route)
	{
		route->route = (t_room **)malloc(sizeof(t_room *) * size);
		if (route->route)
		{
			route->bitroute = NULL;
			route->len = 0;
			route->size = size;
			route->solved = 0;
			route->dead = 0;
			return (route);
		}
	}
	return (NULL);
}

size_t	copy_route(t_route **src, t_route **dst, t_map *map)
{
	size_t	i;

	i = 0;
	while (i < (*src)->len)
	{
		(*dst)->route[i] = (*src)->route[i];
		i++;
	}
	if (bite_route_copy(*dst, *src, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	(*dst)->len = (*src)->len;
	return (EXIT_SUCCESS);
}

static size_t		increase_route_size(t_route **route, t_map *map)
{
	size_t	new_size;
	t_route	*new_route;

	new_size = (*route)->size * 2;
	new_route = setup_route(new_size);
	if (new_route)
	{

		if (copy_route(route, &new_route, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		new_route->size = new_size;
		new_route->len = (*route)->len;
		*route = new_route;
		return (EXIT_SUCCESS);
	}
	/* free things?? */
	return (EXIT_FAILURE);
}

static inline void		bite_route_add_room(t_route *route, const t_room *room)
{
	if (route != NULL && route->bitroute != NULL &&
		room != NULL && room->bitroom != NULL)
	{
		route->bitroute[room->room_i / BITFIELD_SIZE] |=
			room->bitroom[room->room_i / BITFIELD_SIZE];
	}
}

size_t		add_to_route(t_route **curr_route, t_room *room, t_map *map)
{
	if ((*curr_route)->len == (*curr_route)->size)
	{
		if (increase_route_size(curr_route, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	bite_route_add_room(*curr_route, room);
	(*curr_route)->route[(*curr_route)->len] = room;
	(*curr_route)->len++;
	return (EXIT_SUCCESS);
}

/* number of routes */

void		copy_routes(t_route **src, t_route **dst, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

size_t		add_route(t_map *map, t_route *route)
{
	t_route **new_routes;

	new_routes = (t_route **)malloc(sizeof(t_route *) * (map->num_routes + 1));
	if (new_routes)
	{
		copy_routes(map->routes, new_routes, map->num_routes);
		new_routes[map->num_routes] = route;
		map->num_routes++;
		free (map->routes);
		map->routes = new_routes;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

size_t		init_routes(t_map *map)
{
	size_t size;

	size = map->rooms->count / (100 / INIT_ROUTE_PERC);
	if (size == 0)
		size = map->rooms->count;
	map->routes = (t_route **)malloc(sizeof(t_route *));
	if (map->routes)
	{
		map->num_routes = 1;
		map->routes[0] = setup_route(size);
		if (map->routes[0])
		{
			if (bite_alloc(&(map->routes[0]->bitroute), map) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (add_to_route(&map->routes[0], map->end, map) == EXIT_FAILURE)
			{
				handle_error(map);
				return (EXIT_FAILURE);
			}
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
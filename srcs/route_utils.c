/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:34:22 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/22 16:02:59 by lravier       ########   odam.nl         */
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
		if (!route->route)
		{
			free(route);
			return (NULL);
		}
		// bite_alloc()
		route->len = 0;
		route->size = size;
		route->solved = 0;
		route->dead = 0;
	}
	return (route);
}

void	copy_route(t_route **src, t_route **dst)
{
	size_t	i;

	i = 0;
	while (i < (*src)->len)
	{
		(*dst)->route[i] = (*src)->route[i];
		i++;
	}
	(*dst)->len = (*src)->len;
}

static size_t		increase_route_size(t_route **route)
{
	size_t	new_size;
	t_route	*new_route;

	new_size = (*route)->size * 2;
	new_route = setup_route(new_size);
	if (new_route)
	{
		copy_route(route, &new_route);
		new_route->size = new_size;
		new_route->len = (*route)->len;
		*route = new_route;
		return (EXIT_SUCCESS);
	}
	/* free things?? */
	return (EXIT_FAILURE);
}

size_t		add_to_route(t_route **curr_route, t_room *room)
{
	if ((*curr_route)->len == (*curr_route)->size)
	{
		if (increase_route_size(curr_route) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	(*curr_route)->route[(*curr_route)->len] = room;
	(*curr_route)->len++;
	printf("After adding succes\n");
	printf("map start added %d\n",(*curr_route)->solved);
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
			if (add_to_route(&map->routes[0], map->end) == EXIT_FAILURE)
			{
				handle_error(map);
				return (EXIT_FAILURE);
			}
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
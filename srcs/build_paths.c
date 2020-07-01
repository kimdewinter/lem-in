/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_paths.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 19:11:08 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/10 17:13:22 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

size_t		path_contains_conj(t_route *route, t_subpath *pt)
{
	if (((route->bitroute[pt->conj->room_i / BITFIELD_SIZE]) &
	((BITFIELD_TYPE)1 << (63 - pt->conj->room_i % BITFIELD_SIZE))) != 0)
		return (1);
	return (0);
}

t_route			*create_route(size_t len)
{
	t_route	*new;

	new = (t_route *)malloc(sizeof(t_route));
	if (new)
	{
		new->bitroute = NULL;
		new->len = len;
		new->end = 0;
		new->route = (t_room **)malloc(sizeof(t_room *) * len);
		if (new->route)
			return (new);
		free (new);
		return (NULL);
	}
	return (NULL);
}

void			combine_route_subpath(t_room **new, t_route *old, t_subpath *pt)
{
	size_t	i;

	i = 0;
	while (i < old->len)
	{
		new[i] = old->route[i];
		i++;
	}
	i = 0;
	while (i < pt->len)
	{
		new[i + old->len] = pt->path[i];
		i++;
	}
}

t_route			*copy_route(t_route *route, t_subpath *pt, t_map *map)
{
	t_route	*new;

	new = create_route(route->len + pt->len);
	if (new)
	{
		new->last_conj = pt->conj;
		if (copy_bitconj(&(new->bitroute), route->bitroute, map) == EXIT_SUCCESS)
		{
			if (pt->conj != map->end)
				bite_route_add_conj(new, pt->conj);
			combine_route_subpath(new->route, route, pt);
			return (new);
		}
		/* free new route thing */
		return (NULL);
	}
	return (NULL);
}

size_t		add_subpath_cpy_route(t_routes_wrapper *rw, t_route *route,
t_subpath *pt, t_map *map)
{
	t_route	*new;

	if (rw->num_paths == rw->size)
	{
		if (increase_routes_capacity(rw) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	new = copy_route(route, pt, map);
	if (new)
	{
		if (pt->conj == map->end)
			new->end = 1;
		rw->routes[rw->num_paths] = new;
		rw->num_paths++;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

size_t		add_subpath_to_route(t_route *route, t_subpath *pt, t_map *map,
size_t *active)
{
	t_room **new;

	new = (t_room **)malloc(sizeof(t_room *) * (route->len + pt->len));
	if (new)
	{
		if (pt->conj != map->end)
			bite_route_add_conj(route, pt->conj);
		combine_route_subpath(new, route, pt);
		if (pt->conj == map->end)
		{
			(*active)--;
			route->end = 1;
		}
		route->len += pt->len;
		route->last_conj = pt->conj;
		free (route->route);
		route->route = new;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

size_t		add_nbs_to_routes(t_routes_wrapper *rw, t_route *route, t_map *map, 
size_t *active)
{
	size_t		j;
	int			first;
	t_subpath	*add_to_orig;

	j = 0;
	first = 1;
	while (j < route->last_conj->num_options)
	{
		if (path_contains_conj(route, route->last_conj->routes[j]) == 0)
		{
			if (first == 1)
			{
				add_to_orig = route->last_conj->routes[j];
				first = 0;
			}
			else
			{
				if (add_subpath_cpy_route(rw, route, route->last_conj->routes[j],
				map) == EXIT_FAILURE)
					return (EXIT_FAILURE);
				if (route->last_conj->routes[j]->conj != map->end)
					(*active)++;
			}
		}
		j++;
	}
	if (add_subpath_to_route(route, add_to_orig, map, active) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

size_t		solve_paths(t_routes_wrapper *rw, t_map *map, size_t *active)
{
	size_t	i;

	while (*active != 0)
	{
		i = 0;
		while (i < rw->num_paths)
		{
			if (rw->routes[i]->last_conj != map->end)
			{
				if (add_nbs_to_routes(rw, rw->routes[i], map, active)
				== EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else
				rw->routes[i]->end = 1;
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

size_t		build_paths(t_map *map)
{
	t_routes_wrapper	*rw;
	size_t				active;

	active = 0;
	if (setup_routes(&rw, map) == EXIT_SUCCESS &&
	setup_starting_paths(rw, map, &active) == EXIT_SUCCESS &&
	solve_paths(rw, map, &active) == EXIT_SUCCESS)
	{
		map->routes = rw->routes;
		map->num_routes = rw->num_paths;
		free (rw);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
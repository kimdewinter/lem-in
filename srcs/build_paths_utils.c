/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_paths_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 16:44:28 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/12 14:33:24 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void		bite_route_add_conj(t_route *route, const t_room *conj)
{
	route->bitroute[conj->room_i / BITFIELD_SIZE] |=
		(BITFIELD_TYPE)1 << (63 - conj->room_i % BITFIELD_SIZE);
}

size_t	increase_routes_capacity(t_routes_wrapper *rw)
{
	t_route **new;
	size_t	new_size;
	size_t	i;

	i = 0;
	new_size = rw->size * 2;
	new = (t_route **)malloc(sizeof(t_route *) * new_size);
	if (!new)
		return (EXIT_FAILURE);
	rw->size = new_size;
	while (i < rw->num_paths)
	{
		new[i] = rw->routes[i];
		i++;
	}
	free (rw->routes);
	rw->routes = new;
	return (EXIT_SUCCESS);
}

void			set_values_route(t_route *new, t_subpath *pt, t_map *map)
{
	size_t	i;

	i = 0;
	if (pt->conj != map->end)
		bite_route_add_conj(new, pt->conj);
	new->len = pt->len;
	new->end = 0;
	new->ants = 0;
	new->last_conj = pt->conj;
	if (pt->conj == map->end)
		new->end = 1;
	while (i < pt->len)
	{
		new->route[i] = pt->path[i];
		i++;
	}
}

t_route			*setup_route(t_subpath *pt, t_map *map)
{
	t_route *new;

	new = (t_route *)malloc(sizeof(t_route));
	if (new)
	{
		new->route = (t_room **)malloc(sizeof(t_room *) * pt->len);
		if (new->route)
		{
			if (bite_alloc(&(new->bitroute), map) == EXIT_SUCCESS)
			{
				set_values_route(new, pt, map);
				return (new);
			}
			free (new->route);
		}
		free (new);
	}
	return (NULL);
}

size_t	setup_starting_paths(t_routes_wrapper *rw, t_map *map, size_t *active)
{
	size_t	i;

	i = 0;
	rw->num_paths = map->start->num_options;
	while (i < map->start->num_options)
	{
		rw->routes[i] = setup_route(map->start->routes[i], map);
		if (!rw->routes[i])
			return (EXIT_FAILURE);
		if (rw->routes[i]->end == 0)
			(*active)++;
		i++;
	}
	return (EXIT_SUCCESS);
}

size_t	setup_routes(t_routes_wrapper **rw, t_map *map)
{
	*rw = (t_routes_wrapper *)malloc(sizeof(t_routes_wrapper));
	if (!*rw)
		return (EXIT_FAILURE);
	(*rw)->num_paths = 0;
	(*rw)->size = (map->rooms->size * 100) / (100 / INIT_ROUTE_PERC);
	if ((*rw)->size == 0)
		(*rw)->size = (map->rooms->size);
	(*rw)->routes = (t_route **)malloc(sizeof(t_route *) * (*rw)->size);
	if (!(*rw)->routes)
	{
		free (*rw);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

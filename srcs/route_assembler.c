/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_assembler.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 14:45:08 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/03 14:46:38 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t	count_routes(const t_subpath *subpath, const size_t n)
{
	return (subpath == NULL ? n : count_routes(subpath->next_item, n + 1));
}

static ssize_t	assemble_single_route(t_subpath *curr,
										t_route *route,
										size_t route_i,
										const t_map *map)
{
	size_t		segment_i;
	t_subpath	*next;

	segment_i = 0;
	while (segment_i < curr->segment_len)
	{
		route->route[route_i] = curr->path[segment_i];
		route_i++;
		segment_i++;
	}
	route->route[route_i] = curr->conj;
	route_i++;
	next = curr->conj;
	if (curr->path != NULL)
		free(curr->path);
	if (curr->bitconj != NULL)
		free(curr->bitconj);
	free(curr);
	if (next == map->end)
		return (EXIT_SUCCESS);
	else
		return (assemble_single_route(next, route, route_i, map));
}
/*
** links all the nodes of a route together
** also frees the t_subpath (and child array "path") that are no longer needed
*/

static ssize_t	setup_route(t_route **route_ptr,
							const size_t len,
							const BITFIELD_TYPE bitroute,
							const size_t bitfield_len)
{
	size_t	i;

	i = 0;
	(*route_ptr)->bitroute =
		(BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * bitfield_len);
	if ((*route_ptr)->bitroute == NULL)
		return (EXIT_FAILURE);
	while (i < bitfield_len)
	{
		(*route_ptr)->bitroute[i] = bitroute[i];
		i++;
	}
	(*route_ptr)->route = (t_room **)malloc(sizeof(t_room *) * len);
	if ((*route_ptr)->route == NULL)
		return (EXIT_FAILURE);
	(*route_ptr)->last_conj = NULL;
	(*route_ptr)->end = 0;
	(*route_ptr)->len = len;
	(*route_ptr)->ants = 0;
	return (EXIT_SUCCESS);
}
/*
** makes the t_route ready for use
** note that it does not set the 'route' and 'bitroute' arrays to a default val
** since those will be overwritten soon anyhow
*/

ssize_t			assemble_all_routes(t_map *map)
{
	t_subpath	*subp;
	size_t		i;

	if (map == NULL || map->start == NULL ||
		map->start->routes == NULL || map->start->routes[0] == NULL)
		return (EXIT_FAILURE);
	subp = map->start->routes[0];
	map->routes = (t_route **)malloc(sizeof(t_route *) * count_routes(subp, 1));
	if (map->routes == NULL)
		return (EXIT_FAILURE);
	while (subp != NULL)
	{
		if (setup_route(&map->routes[i], subp->len,
			subp->bitconj, map->bitfield_len) == EXIT_FAILURE ||
			assemble_single_route(subp, map->routes[i], 0, map)
			== EXIT_FAILURE)
			return (EXIT_FAILURE);
		subp = subp->next_item;
	}
	return (EXIT_SUCCESS);
}
/*
** converts all the lists of t_subpath nodes into coherent t_routes,
** ready for use by the parallelizer
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_routes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 13:35:43 by kim           #+#    #+#                 */
/*   Updated: 2020/06/30 14:04:32 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void	clean_route(t_route *route, t_map *map)
{
	size_t	i;

	if (route->route != NULL)
	{
		i = 0;
		while (i < route->len)
		{
			route->route[i] = NULL;
			i++;
		}
		route->route = NULL;
	}
	route->len = 0;
	if (route->bitroute != NULL)
	{
		free(route->bitroute);
		route->bitroute = NULL;
	}
	route->last_conj = NULL;
	route->end = NULL;
	route->ants = -1;
}

void	clean_routes(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->num_routes)
	{
		if (map->routes[i] != NULL)
		{
			clean_route(map->routes[i], map);
			map->routes[i] = NULL;
		}
		i++;
	}
	free(map->routes);
	map->routes = NULL;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bfs_resize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 15:01:12 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/29 15:01:12 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t		increase_route_size(t_bfs_route *bfs_route)
{
	size_t	new_size;
	t_room	**new_route;
	size_t	i;

	i = 0;
	new_size = bfs_route->len * 2;
	new_route = create_new_route(new_size);
	if (new_route)
	{
		while (i < bfs_route->used)
		{
			new_route[i] = bfs_route->route[i];
			i++;
		}
		bfs_route->len = new_size;
		free (bfs_route->route);
		bfs_route->route = new_route;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

ssize_t		increase_vault_size(t_bfs_vault *vault, t_map *map)
{
	size_t		new_size;
	size_t		i;
	t_bfs_route	**new_bfs_routes;

	i = 0;
	if (vault->len == 0)
	{
		new_size = (map->rooms->count * 100) / ((100 / INIT_ROUTE_PERC) * 100);
		if (new_size == 0)
			new_size = map->rooms->count;
	}
	else
		new_size = vault->len * 2;
	new_bfs_routes = (t_bfs_route **)malloc(sizeof(t_bfs_route *) * new_size);
	if (new_bfs_routes)
	{
		while (i < vault->used)
		{
			new_bfs_routes[i] = vault->routes[i];
			i++;
		}
		vault->len = new_size;
		if (vault->routes)
			free (vault->routes);
		vault->routes = new_bfs_routes;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
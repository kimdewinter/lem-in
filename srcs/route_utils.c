/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 13:24:02 by kim           #+#    #+#                 */
/*   Updated: 2020/05/15 14:42:29 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static ssize_t	handle_error(t_map *map)
{
	size_t		i;
	size_t		j;
	// Free the stuff
	i = 0;
	if (map->end->routes != NULL)
	{
		while (i < map->end->neighbours_len && map->end->routes[i] != NULL)
		{
			j = 0;
			while (j < map->end->routes[i]->len && map->end->routes[i]->route[j] != NULL)
			{
				free(map->end->routes[i]->route[j]);
				j++;
			}
			free(map->end->routes[i]);
			i++;
		}
		free(map->end->routes);
	}
	return (EXIT_FAILURE);
}

ssize_t		route_new(t_map *map)
{
	size_t	initial_route_size;
	size_t	i;

	initial_route_size = map->rooms->count / (100 / INIT_ROUTE_PERC);
	if (initial_route_size < 1)
		initial_route_size = map->rooms->count;
	map->end->routes_len = map->end->neighbours_len;
	map->end->routes = (t_route **)malloc(sizeof(t_route *) * map->end->neighbours_len);
	if (map->end->routes != NULL)
	{
		i = 0;
		while (i < map->end->neighbours_len)
		{
			map->end->routes[i] = (t_route *)malloc(sizeof(t_route) * initial_route_size);
			if (map->end->routes[i] != NULL)
			{
				map->end->routes[i]->len = initial_route_size;
				map->end->routes[i]->route = (t_room **)malloc(sizeof(t_route *) * initial_route_size);
				if (map->end->routes[i]->route != NULL)
				{
					map->end->routes[i]->route[0] = map->end;
					ft_bzero(&(map->end->routes[i]->route[1]), initial_route_size - 1);
					i++;
				}
				else
					return (handle_error(map));
			}
			else
				return (handle_error(map));
		}
		return (EXIT_SUCCESS);
	}
	return (handle_error(map));
}

ssize_t		route_copy(t_map *map, t_room *room)
{
	
}

// ssize_t		route_init;

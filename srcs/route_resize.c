/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_resize.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 13:33:39 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/28 14:56:46 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t			increase_route_size(t_subpath **pt, t_map *map)
{
	t_subpath	*tmp;
	size_t		new_size;
	t_room		**new_route;
	size_t		i;
	ssize_t		j;

	tmp = *pt;
	if (tmp->size == 0)
	{
		new_size = (map->rooms->count * 100) / ((100 / INIT_ROUTE_PERC) * 100);
		if (new_size == 0)
			new_size = map->rooms->count;
	}
	else
		new_size = tmp->size * 2;
	i = new_size - 1;
	j = (*pt)->size - 1;
	new_route = new_path(new_size);
	if (new_route)
	{
		while (j >= 0)
		{
			new_route[i] = tmp->path[j];
			j--;
			i--;
		}
		free ((*pt)->path);
		(*pt)->path = new_route;
		(*pt)->size = new_size;
		(*pt)->start_ind = i;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

ssize_t			increase_routes_size(t_room **dst, t_map *map)
{
	size_t		i;
	size_t		new_size;
	t_subpath	**new_routes;

	i = 0;
	if ((*dst)->routes_size == 0)
	{
		new_size = (map->rooms->count * 100) / ((100 / INIT_ROUTE_PERC) * 100);
		if (new_size == 0)
			new_size = map->rooms->count;
	}
	else
		new_size = (*dst)->routes_size * 2;
	new_routes = (t_subpath **)malloc(sizeof(t_subpath *) * new_size);
	if (new_routes)
	{
		while (i < (*dst)->routes_size)
		{
			new_routes[i] = (*dst)->routes[i];
			i++;
		}
		if ((*dst)->routes)
			free ((*dst)->routes);
		(*dst)->routes = new_routes;
		(*dst)->routes_size = new_size;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
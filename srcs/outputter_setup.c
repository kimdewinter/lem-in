/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   outputter_setup.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 16:51:36 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/24 16:55:05 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	copy_roomnames(char ***rooms, t_route *curr)
{
	size_t	i;

	i = 0;
	*rooms = (char **)malloc(sizeof(char *) * curr->used);
	if (*rooms == NULL)
		return (EXIT_FAILURE);
	while (i < curr->used)
	{
		(*rooms)[i] = curr->route[i]->name;
		i++;
	}
	return (EXIT_SUCCESS);
}

static ssize_t	setup_ants(size_t **ants, size_t len)
{
	size_t	i;

	i = 0;
	*ants = (size_t *)malloc(sizeof(size_t) * len);
	if (*ants == NULL)
		return (EXIT_FAILURE);
	while (i < len)
	{
		(*ants)[i] = 0;
		i++;
	}
	return (EXIT_SUCCESS);
}

static ssize_t	setup_routeput(t_routeput **new, t_route *curr)
{
	*new = (t_routeput *)malloc(sizeof(t_routeput));
	if (*new)
	{
		if (copy_roomnames(&(*new)->rooms, curr) == EXIT_SUCCESS)
		{
			if (setup_ants(&(*new)->ants, curr->used) == EXIT_SUCCESS)
			{
				(*new)->rooms_len = curr->used;
				(*new)->ants_received = 0;
				(*new)->finished = 0;
				return (EXIT_SUCCESS);
			}
			free((*new)->rooms);
		}
		free(*new);
	}
	return (EXIT_FAILURE);
}

ssize_t			setup_all_routeputs(t_routeput ***routes, const t_map *map)
{
	size_t		i;

	*routes = (t_routeput **)malloc(sizeof(t_routeput *) * map->solution.used);
	if (*routes == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < map->solution.used)
	{
		setup_routeput(&(*routes)[i], map->solution.combi[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

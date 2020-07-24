/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 14:33:23 by kim           #+#    #+#                 */
/*   Updated: 2020/07/24 18:09:44 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	find_route(const t_route *parent,
							t_room *branch_to,
							t_map *map)
{
	t_route	*route;

	if (allocopy_route(&route, parent, branch_to, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

static ssize_t	init_find_route(const t_room *start_neighbour, t_map *map)
{
	(void)start_neighbour;
	(void)find_route(NULL, NULL, NULL);
	(void)map;
	return (EXIT_SUCCESS);
}

ssize_t			find_routes(t_map *map)
{
	size_t	i;

	if (map->start == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < map->start->neighbours_len)//what if start has no neighbours?
	{
		if (init_find_route(map->start->neighbours[i], map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

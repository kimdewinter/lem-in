/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bfs.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 13:37:28 by kim           #+#    #+#                 */
/*   Updated: 2020/07/29 15:14:02 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"



static ssize_t	grow_route(t_bfs_route *route,
							t_bfs_vault *vault,
							const t_map *map)
{
	t_room	*room;
	size_t	i;

	if (route->next_to_add == map->end)// if true, shortest has been found
	{
		vault->shortest = route;
		return (EXIT_SUCCESS);
	}
	if (add_room(route) == EXIT_FAILURE)// add next_to_add to route->route
		return (EXIT_FAILURE);
	i = 0;
	while (i < room->neighbours_len)
	{
		if (i + 1 == room->neighbours_len)// one remaining, can use current t_bfs_route
		{
			route->next_to_add = room->neighbours[i];
		}
		else if (branch_route(route, vault, room->neighbours[i], map) ==
			EXIT_FAILURE)// multiple remaining, must copy-branch t_bfs_route
		{
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

ssize_t			bfs_shortest(t_map *map)
{
	t_bfs_vault	vault;

	if (bite_bitroute_copy(vault.visited, map->start->bitroom, map) ==
		EXIT_FAILURE ||
		setup_vault(&vault) == EXIT_FAILURE)
		return (EXIT_FAILURE);
}
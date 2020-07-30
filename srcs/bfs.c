/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bfs.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 13:37:28 by kim           #+#    #+#                 */
/*   Updated: 2020/07/30 13:18:45 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"



static ssize_t	grow_route(t_bfs_route *route,
							t_bfs_vault *vault,
							const t_map *map)
{
	t_room	*room;
	size_t	i;

	room = route->next_to_add;
	if (room == map->end && add_room(route, room))// if true, shortest has been found
	{
		vault->shortest = route;
		return (EXIT_SUCCESS);
	}
	if (bite_add_room_to_bitfield(vault->visited, room->bitroom)
		== EXIT_FAILURE || add_room(route, room) == EXIT_FAILURE)// add next_to_add to route->route
		return (EXIT_FAILURE);
	i = 0;
	while (i < room->neighbours_len)
	{
		if (i + 1 == room->neighbours_len)// one remaining, can use current t_bfs_route
		{
			if (room_in_bitfield(room->neighbours[i], vault->visited) == 0)
				route->next_to_add = room->neighbours[i];
		}
		else if (room_in_bitfield(room->neighbours[i], vault->visited) == 0)
		{
			if (branch_route(route, vault, room->neighbours[i], map) ==
				EXIT_FAILURE))// multiple remaining, must copy-branch t_bfs_route
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

ssize_t			bfs_shortest(t_map *map)
{
	t_bfs_vault	vault;
	size_t		i;

	vault.len = 0;
	vault.used = 0;
	vault.shortest = NULL;
	if (bite_bitroute_copy(vault.visited, map->start->bitroom, map) ==
		EXIT_FAILURE)
		return (EXIT_FAILURE);//add start room to visited
	if (branch_route(NULL, &vault, map->start->neighbours[i], map) ==
		EXIT_FAILURE ||
		add_room(vault.routes[vault.used - 1], map->start) == EXIT_FAILURE)
		return (EXIT_FAILURE);// set up initial neighbours of start
	while (vault.shortest == NULL && vault.used > 0)
	{
		i = 0;
		while (i < vault.len && vault.shortest == NULL)//possibility of two equally short routes being found, only one is kept
		{
			if (grow_route(vault.routes[i], &vault, map) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			i++;
		}
	}
}

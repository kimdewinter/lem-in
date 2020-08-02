/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bfs_shortest.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 13:37:28 by kim           #+#    #+#                 */
/*   Updated: 2020/07/31 15:30:12 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	grow_route_neighbourhood(t_bfs_route *route,
											t_room *room,
											t_bfs_vault *vault,
											const t_map *map)
{
	size_t	i;

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
			if (branch_bfs_route(route, vault, room->neighbours[i], map) ==
				EXIT_FAILURE)// multiple remaining, must copy-branch t_bfs_route
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static ssize_t	grow_route(t_bfs_route *route,
							t_bfs_vault *vault,
							const t_map *map)
{
	t_room	*room;

	room = route->next_to_add;
	if (room == map->end && add_bfs_room(route, room))// if true, shortest has been found
	{
		vault->shortest = route;
		return (EXIT_SUCCESS);
	}
	if (bite_add_room_to_bitfield(vault->visited, room->bitroom, map)
		== EXIT_FAILURE || add_bfs_room(route, room) == EXIT_FAILURE)// add next_to_add to route->route
		return (EXIT_FAILURE);
	if (grow_route_neighbourhood(route, room, vault, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static ssize_t	setup_vault(t_bfs_vault *vault, const t_map *map)
{
	size_t	i;

	vault->len = 0;
	vault->used = 0;
	vault->shortest = NULL;
	if (bite_alloc_noval(&vault->visited, map) == EXIT_FAILURE ||
		bite_bitroute_copy(vault->visited, map->start->bitroom, map) ==
		EXIT_FAILURE)
		return (EXIT_FAILURE);//add start room to visited
	i = 0;
	while (i < map->start->neighbours_len)
	{
		if (branch_bfs_route(NULL, vault, map->start->neighbours[i], map) ==
			EXIT_FAILURE ||
			add_bfs_room(vault->routes[vault->used - 1], map->start) == EXIT_FAILURE)
			return (EXIT_FAILURE);// set up initial neighbours of start
		vault->used++;
		i++;
	}
	vault->next_rnd_used = vault->used;
	return (EXIT_SUCCESS);
}

ssize_t			bfs_shortest(t_map *map)
{
	t_bfs_vault	vault;
	size_t		i;

	if (setup_vault(&vault, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (vault.shortest == NULL && vault.used > 0)
	{
		i = 0;
		while (i < vault.len && vault.shortest == NULL)//possibility of two equally short routes being found, only one is kept
		{
			if (vault.routes[i] != NULL)
				if (grow_route(vault.routes[i], &vault, map) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			i++;
		}
		vault.used = vault.next_rnd_used;
	}
	return (EXIT_SUCCESS);
}

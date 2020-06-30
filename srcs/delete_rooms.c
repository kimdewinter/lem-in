/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_rooms.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 15:19:42 by kim           #+#    #+#                 */
/*   Updated: 2020/06/30 15:47:42 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void	delete_address_array(void ***array_address, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		(*array_address)[i] = NULL;
		i++;
	}
	free(*array_address);
	*array_address = NULL;
}

static void	delete_single_room(t_room *room)
{
	size_t	i;

	room->sps = 0;
	room->spe = 0;
	if (room->name != NULL)
	{
		free(room->name);
		room->name = NULL;
	}
	room->xpos = -1;
	room->ypos = -1;
	room->ant = 0;
	if (room->neighbours)
		delete_address_array(&room->neighbours, room->neighbours_len);
	room->neighbours_len = 0;
	room->room_i = 0;
	room->num_options = 0;
	if (room->routes != NULL)
		delete_address_array(&room->routes, room->routes_size);
	room->routes_size = 0;
	if (room->bitconj != NULL)
	{
		free(room->bitconj);
		room->bitconj = NULL;
	}
}

void		delete_all_rooms(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->rooms->size)
	{
		if (map->rooms->entries[i] != NULL)
		{
			delete_single_room(map->rooms->entries[i]->val);
			free(map->rooms->entries[i]->val);
			map->rooms->entries[i]->val = NULL;
		}
		i++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   biter.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:13:42 by kim           #+#    #+#                 */
/*   Updated: 2020/05/21 16:15:24 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static ssize_t	bite_alloc(BITFIELD_TYPE **dest, const size_t bitfield_len)
{
	size_t	i;

	if (*dest == NULL)
	{
		*dest = (BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * bitfield_len);
		if (*dest != NULL)
		{
			i = 0;
			while (i < bitfield_len)
			{
				dest[i] = (BITFIELD_TYPE)0;
				i++;
			}
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

ssize_t			bite_room_new(t_room *room, const t_map *map)
{
	size_t	i;

	if (room != NULL && room->bitroom == NULL &&
		alloc_bitfield(&(room->bitroom), map->bitfield_len) == EXIT_SUCCESS)
	{
		i = 0;
		while (i < map->bitfield_len)
		{
			room->bitroom[i] = (i == room->room_i / BITFIELD_SIZE) ?
				(BITFIELD_TYPE)1 << 63 - room->room_i % BITFIELD_SIZE:
				(BITFIELD_TYPE)0;
			i++;
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
/*
** takes a room and stores it's bitfield-form in room->bitroom
*/

inline void		bite_route_add_room(t_route *route, const t_room *room)
{
	if (route != NULL && route->bitroute != NULL &&
		room != NULL && room->bitroom != NULL)
	{
		route->bitroute[room->room_i / BITFIELD_SIZE] |=
			room->bitroom[room->room_i / BITFIELD_SIZE];
	}
}
/*
** takes a bitfield-form route and flips on a room's bit in it
** WARNING: this is an inline void fn for performance reasons
** (to increase odds of being inlined),
** it will not return success or failure so use with care
*/

ssize_t			bite_route_new(t_route *route, const t_map *map)
{
	size_t	i;

	if (route != NULL && route->route != NULL && route->bitroute == NULL &&
		bite_alloc(&(route->bitroute), map->bitfield_len) == EXIT_SUCCESS)
	{
		i = 0;
		while (i < route->len)
		{
			if (route->route[i] != NULL)
				bite_route_add_room(route, route->route[i]);
			i++;
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
/*
** takes the route->route array and stores it in bitfield-form in route->bitroute
*/

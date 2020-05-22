/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   biter.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:13:42 by kim           #+#    #+#                 */
/*   Updated: 2020/05/21 16:43:42 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static ssize_t	bite_alloc(BITFIELD_TYPE **dst, const t_map *map)
{
	size_t	i;

	if (*dst == NULL)
	{
		*dst = (BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * map->bitfield_len);
		if (*dst != NULL)
		{
			i = 0;
			while (i < map->bitfield_len)
			{
				dst[i] = (BITFIELD_TYPE)0;
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

ssize_t			bite_route_convert(t_route *route, const t_map *map)
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

ssize_t			bite_route_copy(t_route *dst,
								const t_route *src,
								const t_map *map)
{
	size_t	i;

	if (dst == NULL && src != NULL && src->bitroute != NULL)
	{
		dst->bitroute = 
			(BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * map->bitfield_len);
		if (dst->bitroute != NULL)
		{
			i = 0;
			while (i < map->bitfield_len)
			{
				dst->bitroute[i] = src->bitroute[i];
				i++;
			}
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
/*
** copies one route's bitfield-form route into another's
*/

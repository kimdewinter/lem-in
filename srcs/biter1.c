/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   biter1.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:13:42 by kim           #+#    #+#                 */
/*   Updated: 2020/06/13 12:51:53 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

ssize_t	bite_alloc(BITFIELD_TYPE **dst, const t_map *map)
{
	size_t	i;

	*dst =
		(BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * map->bitfield_len);
	if (*dst == NULL)
		return (handle_err_biter(1, "bite_alloc\n"));
	i = 0;
	while (i < map->bitfield_len)
	{
		(*dst)[i] = (BITFIELD_TYPE)0;
		i++;
	}
	return (EXIT_SUCCESS);
}

ssize_t	bite_alloc_noval(BITFIELD_TYPE **dst, const t_map *map)
{
	*dst =
		(BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * map->bitfield_len);
	if (*dst == NULL)
		return (handle_err_biter(1, "bite_alloc_noval\n"));
	return (EXIT_SUCCESS);
}

// ssize_t			bite_room_new(t_room *room, const t_map *map)
// {
// 	size_t	i;

// 	i = room->room_i / BITFIELD_SIZE;
// 	if (bite_alloc(&(room->bitroom), map) == EXIT_SUCCESS)
// 	{
// 		if (room == map->start || room == map->end)//TEMP FIX:
// 			return (EXIT_SUCCESS);//to avoid bitroutes colliding
// 			//(being seen as incompatible combinations) due to both having
// 			//the start and end room in it
// 		room->bitroom[i] = (BITFIELD_TYPE)1 <<
// 		(63 - room->room_i % BITFIELD_SIZE);
// 		return (EXIT_SUCCESS);
// 	}
// 	return (EXIT_FAILURE);
// }
/*
** takes a room and stores it's bitfield-form in room->bitroom
*/

// static inline void		bite_route_add_room(t_route *route, const t_room *room)
// {
// 	route->bitroute[room->room_i / BITFIELD_SIZE] |=
// 		room->bitroom[room->room_i / BITFIELD_SIZE];
// }
/*
** takes a bitfield-form route and flips on a room's bit in it
** WARNING: this is an inline void fn for performance reasons
** (to increase odds of being inlined),
** it will not return success or failure so use with care
*/

// ssize_t			bite_route_convert(t_route *route, const t_map *map)
// {
// 	size_t	i;

// 	if (bite_alloc(&(route->bitroute), map) != EXIT_SUCCESS)
// 		return (EXIT_FAILURE);
// 	i = 0;
// 	while (i < route->len)
// 	{
// 		if (route->route[i] != NULL)
// 			bite_route_add_room(route, route->route[i]);
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }
/*
** takes the route->route array and stores it in bitfield-form in route->bitroute
*/

// ssize_t			bite_route_copy(t_route *dst,
// 								const t_route *src,
// 								const t_map *map)
// {
// 	size_t	i;

// 	dst->bitroute = 
// 		(BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * map->bitfield_len);
// 	if (dst->bitroute == NULL)
// 		return (handle_err_biter(1, "bite_route_copy\n"));
// 	i = 0;
// 	while (i < map->bitfield_len)
// 	{
// 		dst->bitroute[i] = src->bitroute[i];
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }
/*
** copies one route's bitfield-form route into another's
*/

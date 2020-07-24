/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 14:51:00 by kim           #+#    #+#                 */
/*   Updated: 2020/07/24 18:10:13 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

inline static void	alloc_route(t_route **dst,
									const size_t route_len,
									const size_t route_len_used,
									const size_t bitfield_len)
{
	*dst = (t_route *)malloc(sizeof(t_route) * 1);
	if (*dst != NULL)
	{
		(*dst)->len = route_len;
		(*dst)->route = (t_room **)malloc(sizeof(t_room *) * route_len);
		(*dst)->used = route_len_used;
		(*dst)->bitroute =
			(BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * bitfield_len);
		(*dst)->ants = 0;
	}
}

ssize_t			allocopy_route(t_route **dst,
								const t_route *src,
								t_room *room_to_add,
								const t_map *map)
{
	size_t	i;

	alloc_route(dst, map->rooms->count, src->used + 1, map->bitfield_len);
	if (*dst == NULL || (*dst)->route == NULL || (*dst)->bitroute == NULL)
		return (handle_err_route_finder(1, "allocate_route\n"));
	i = 0;
	while (i < (*dst)->len)
	{
		(*dst)->route[i] = src->route[i];
		i++;
	}
	(*dst)->route[src->used] = room_to_add;
	while (i < map->bitfield_len)
	{
		(*dst)->bitroute[i] = src->bitroute[i];
		i++;
	}
	(*dst)->bitroute[room_to_add->room_i / BITFIELD_SIZE] |=
		room_to_add->bitroom[room_to_add->room_i / BITFIELD_SIZE];
	return (EXIT_SUCCESS);
}

ssize_t			allocinit_singleroom_route(t_route **dst,
											t_room *first_room,
											const t_map *map)
{
	size_t	i;

	alloc_route(dst, map->rooms->count, 1, map->bitfield_len);
	if (*dst == NULL || (*dst)->route == NULL || (*dst)->bitroute == NULL)
		return (handle_err_route_finder(1, "allocate_route\n"));
	i = 1;
	while (i < (*dst)->len)
	{
		(*dst)->route[i] = NULL;
		i++;
	}
	(*dst)->route[0] = first_room;
	while (i < map->bitfield_len)
	{
		(*dst)->bitroute[i] = (BITFIELD_TYPE)0;
		i++;
	}
	(*dst)->bitroute[first_room->room_i / BITFIELD_SIZE] |=
		first_room->bitroom[first_room->room_i / BITFIELD_SIZE];
	return (EXIT_SUCCESS);
}

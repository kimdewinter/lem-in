/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 14:51:00 by kim           #+#    #+#                 */
/*   Updated: 2020/07/23 15:28:24 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	allocopy_rooms(t_route **dst,
								const t_route *src,
								t_room *room_to_add)
{
	size_t	i;

	(*dst)->route = (t_room **)malloc(sizeof(t_room *) * (*dst)->len);
	if ((*dst)->route == NULL)
		return (handle_err_route_finder(1, "allocopy_rooms"));
	i = 0;
	while (src->route[i] != NULL)
	{
		(*dst)->route[i] = src->route[i];
		i++;
	}
	(*dst)->route[i] = room_to_add;
	i++;
	while (i < (*dst)->len)
	{
		(*dst)->route[i] = NULL;
		i++;
	}
	return (EXIT_SUCCESS);
}

ssize_t			allocopy_route(t_route **dst,
								const t_route *src,
								t_room *room_to_add,
								const t_map *map)
{
	size_t	i;

	*dst = (t_route *)malloc(sizeof(t_route) * 1);
	if (*dst == NULL)
		return handle_err_route_finder(1, "allocopy_route\n");
	(*dst)->len = map->rooms->count + 1;//would a vector be faster or slower?
	if (allocopy_rooms(dst, src, room_to_add) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	(*dst)->ants = 0;
	(*dst)->bitroute =
		(BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * map->bitfield_len);
	if ((*dst)->bitroute == NULL)
		return handle_err_route_finder(1, "allocopy_route\n");
	i = 0;
	while (i < map->bitfield_len)
	{
		(*dst)->bitroute[i] = src->bitroute[i];
		i++;
	}
	(*dst)->bitroute[room_to_add->room_i / BITFIELD_SIZE] |=
		room_to_add->bitroom[room_to_add->room_i / BITFIELD_SIZE];
	return (EXIT_SUCCESS);
}

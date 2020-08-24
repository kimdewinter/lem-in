/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_sps.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 12:03:01 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/24 12:18:47 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		set_sps(t_room *prev, t_room *curr, size_t dist)
{
	if (curr->sps == 1)
	{
		if (curr->sps_len > dist)
		{
			curr->sps_len = dist;
			curr->sps_start = prev;
		}
	}
	else
	{
		curr->sps = 1;
		curr->sps_len = dist;
		curr->sps_start = prev;		
	}
}

static void		continue_sps(t_room *start, BITFIELD_TYPE *visited, size_t dist,
t_map *map)
{
	ssize_t	i;

	i = 0;
	if (start->is_junction == 1)
		return ;
	bite_add_room_to_bitfield(start, visited);
	while ((size_t)i < start->neighbours_len)
	{
		if (room_in_bitfield(start->neighbours[i], visited) == 0)
		{
			set_sps(start, start->neighbours[i], dist);
			continue_sps(start->neighbours[i], visited, dist + 1, map);
		}
		i++;
	}
}

ssize_t		set_sps_rooms(t_map *map)
{
	BITFIELD_TYPE	*visited;
	ssize_t			i;
	size_t			dist;

	i = 0;
	dist = 1;
	if (bite_alloc(&visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	bite_add_room_to_bitfield(map->start, visited);
	while ((size_t)i < map->start->neighbours_len)
	{
		set_sps(map->start, map->start->neighbours[i], dist);
		continue_sps(map->start->neighbours[i], visited, dist + 1, map);
		i++;
	}
	free (visited);
	return (EXIT_SUCCESS);
}
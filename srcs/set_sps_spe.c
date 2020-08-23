/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_sps_spe.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 17:57:38 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/23 20:07:45 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		set_spe(t_room *prev, t_room *curr, size_t dist, t_map *map)
{
	if (curr->spe == 1 && curr != map->start)
	{
		if (curr->spe_len > dist)
		{
			curr->spe_len = dist;
			curr->spe_start = prev;
		}
	}
	else
	{
		curr->spe = 1;
		curr->spe_len = dist;
		curr->spe_start = prev;		
	}
}

static void		continue_spe(t_room *start, BITFIELD_TYPE *visited, size_t dist,
t_map *map)
{
	ssize_t	i;
	int		moved;

	i = 0;
	moved = 0;
	if (start->is_junction == 1)
		return ;
	bite_add_room_to_bitfield(start, visited);
	while ((size_t)i < start->neighbours_len)
	{
		if (room_in_bitfield(start->neighbours[i], visited) == 0)
		{
			set_spe(start, start->neighbours[i], dist, map);
			continue_spe(start->neighbours[i], visited, dist + 1, map);
		}
		if (moved == 0)
			i++;
		moved = 0;
	}
}

ssize_t		set_spe_rooms(t_map *map)
{
	BITFIELD_TYPE	*visited;
	ssize_t			i;
	size_t			dist;

	i = 0;
	dist = 1;
	if (bite_alloc(&visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	bite_add_room_to_bitfield(map->end, visited);
	while ((size_t)i < map->end->neighbours_len)
	{
		set_spe(map->end, map->end->neighbours[i], dist, map);
		continue_spe(map->end->neighbours[i], visited, dist + 1, map);
		i++;
	}
	free (visited);
	return (EXIT_SUCCESS);	
}

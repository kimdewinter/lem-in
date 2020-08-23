/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_sps_spe.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 17:57:38 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/23 16:58:43 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		set_sps(t_room *prev, t_room *curr, size_t dist, t_map *map)
{
	int	res;

	res = 0;
	if (curr->sps == 1 && curr != map->end)
	{
		if (curr->sps_len <= dist)
		{
			del_tube(prev, curr, map);
			res = del_tube(curr, prev, map);
			return (res);
		}
		else
		{
			del_tube(curr->sps_start, curr, map);
			del_tube(curr, curr->sps_start, map);	
		}
	}
	curr->sps = 1;
	curr->sps_len = dist;
	curr->sps_start = prev;
	return (0);
}

int		set_spe(t_room *prev, t_room *curr, size_t dist, t_map *map)
{
	int		res;

	res = 0;
	if (curr->spe == 1 && curr != map->start)
	{
		if (curr->spe_len <= dist)
		{
			del_tube(prev, curr, map);
			res = del_tube(curr, prev, map);
			return (res);
		}
		else
		{
			del_tube(curr->spe_start, curr, map);
			del_tube(curr, curr->spe_start, map);	
		}
	}
	curr->spe = 1;
	curr->spe_len = dist;
	curr->spe_start = prev;
	return (res);
}

void		continue_sps(t_room *start, BITFIELD_TYPE *visited, size_t dist,
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
			moved = set_sps(start, start->neighbours[i], dist, map);
			if (moved == 0)
				continue_sps(start->neighbours[i], visited, dist + 1, map);
		}
		if (moved == 0)
			i++;
		moved = 0;
	}
}

void		continue_spe(t_room *start, BITFIELD_TYPE *visited, size_t dist,
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
			moved = set_spe(start, start->neighbours[i], dist, map);
			if (moved == 0)
				continue_spe(start->neighbours[i], visited, dist + 1, map);
		}
		if (moved == 0)
			i++;
		moved = 0;
	}
}

ssize_t		set_sps_rooms(t_map *map)
{
	BITFIELD_TYPE	*visited;
	ssize_t			i;
	int				moved;
	size_t			dist;

	i = 0;
	dist = 1;
	moved = 0;
	if (bite_alloc(&visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	bite_add_room_to_bitfield(map->start, visited);
	while ((size_t)i < map->start->neighbours_len)
	{
		moved = 0;
		moved = set_sps(map->start, map->start->neighbours[i], dist, map);
		if (moved == 0)
		{
			continue_sps(map->start->neighbours[i], visited, dist + 1, map);
			i++;
		}
		moved = 0;
	}
	free (visited);
	return (EXIT_SUCCESS);	
}

ssize_t		set_spe_rooms(t_map *map)
{
	BITFIELD_TYPE	*visited;
	ssize_t			i;
	int				moved;
	size_t			dist;

	i = 0;
	dist = 1;
	moved = 0;
	if (bite_alloc(&visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	bite_add_room_to_bitfield(map->end, visited);
	while ((size_t)i < map->end->neighbours_len)
	{
		moved = 0;
		moved = set_spe(map->end, map->end->neighbours[i], dist, map);
		if (moved == 0)
		{
			continue_spe(map->end->neighbours[i], visited, dist + 1, map);
			i++;
		}
		moved = 0;
	}
	free (visited);
	return (EXIT_SUCCESS);	
}

ssize_t		set_sps_spe_rooms(t_map *map)
{
	if (set_sps_rooms(map) == EXIT_FAILURE
	|| set_spe_rooms(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_blockage_2.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 10:47:21 by lravier       #+#    #+#                 */
/*   Updated: 2020/09/30 16:50:18 by simoncleerd   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void				find_block_in_path(t_route *route, t_room **from,
t_room **to)
{
	ssize_t	i;
	t_room	*tmp;

	i = 0;
	tmp = *from;
	while ((size_t)i < route->used - 1)
	{
		if (route->route[i] == tmp)
		{
			*to = route->route[i];
			*from = route->route[i + 1];
			break ;
		}
		i++;
	}
	i--;
}

ssize_t					remove_conn(t_best *candidate, t_room *block,
t_map *map)
{
	size_t	i;
	t_room	*next;

	i = 0;
	next = NULL;
	while (i < candidate->used)
	{
		if (room_in_bitfield(block, candidate->combi[i]->bitroute) == 1)
		{
			find_block_in_path(candidate->combi[i], &block, &next);
			del_tube(block, next, map);
			del_tube(next, block, map);
			set_spe_rooms(map);
			set_sps_rooms(map);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

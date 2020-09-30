/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_blockage_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/30 17:18:05 by lravier       #+#    #+#                 */
/*   Updated: 2020/09/30 17:23:36 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int			check_valid_candidate_block(t_room *start, size_t j,
BITFIELD_TYPE *visited)
{
	if (room_in_bitfield(start->neighbours[j], visited) == 0
	&& start->neighbours[j]->dist_to_start >= 0
	&& start->neighbours[j]->dist_to_start < start->dist_to_start)
		return (1);
	return (0);
}

ssize_t		handle_return_block(t_best *candidate, t_room *found, t_map *map)
{
	if (found != NULL)
	{
		if (remove_conn(candidate, found, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_NO_BLOCKS);
}

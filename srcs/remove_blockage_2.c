/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_blockage_2.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 10:47:21 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/17 10:57:15 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static t_room			*find_next_node(t_route *route, t_room *block)
{
	size_t	i;

	i = 0;
	while (i < route->used)
	{
		if (route->route[i] == block)
			return (route->route[i + 1]);
		i++;
	}
	return (NULL);
}

ssize_t					setup_in_paths(t_best *state, BITFIELD_TYPE **in_paths,
t_map *map)
{
	size_t	i;

	i = 0;
	if (bite_alloc(in_paths, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (i < state->used)
	{
		merge_bitfield(*in_paths, state->combi[i]->bitroute, map);
		i++;
	}
	return (EXIT_SUCCESS);
}

ssize_t					remove_conn(t_best *state, t_room *block, t_map *map)
{
	size_t	i;
	t_room	*next;

	i = 0;
	while (i < state->used)
	{
		if (room_in_bitfield(block, state->combi[i]->bitroute) == 1)
		{
			next = find_next_node(state->combi[i], block);
			if (next == NULL)
				return (EXIT_FAILURE);
			del_tube(block, next, map);
			del_tube(next, block, map);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

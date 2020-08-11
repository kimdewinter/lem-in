/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_blockage.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/10 13:17:29 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/10 13:17:29 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

static ssize_t	setup_in_paths(t_best *state, BITFIELD_TYPE **in_paths, t_map *map)
{
	size_t	i;

	i = 0;
	if (bite_alloc(in_paths, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (i < state->used)
	{
		merge_bitfield(*in_paths ,state->combi[i]->bitroute, map);
		i++;
	}
}

static int	find_most_promising_start(t_room *start, BITFIELD_TYPE *visited,
BITFIELD_TYPE *in_paths, size_t *i)
{
	size_t	best;
	size_t	j;

	*i = 0;
	j = *i;
	best = -1;
	while (j < start->neighbours_len)
	{
		if (room_in_bitfield(start->neighbours[j], visited) == 0
		&& room_in_bitfield(start->neighbours[j], in_paths) == 0)
		{
			if (best == -1)
				best = j;
			else
			{
				if (start->neighbours[j]->dist_to_start
				< start->neighbours[best]->dist_to_start)	
					best = j;
			}
		}
		j++;
	}
	*i = best;
	if (best == -1)
		return (0);
	return (1);
}

static int	find_most_promising(t_room *start, BITFIELD_TYPE *visited, size_t *i)
{
	size_t	best;
	size_t	j;

	*i = 0;
	j = *i;
	best = -1;
	while (j < start->neighbours_len)
	{
		if (room_in_bitfield(start->neighbours[j], visited) == 0)
		{
			if (best == -1)
				best = j;
			else
			{
				if (start->neighbours[j]->dist_to_start
				< start->neighbours[best]->dist_to_start)	
					best = j;
			}
		}
		j++;
	}
	*i = best;
	if (best == -1)
		return (0);
	return (1);
}

t_room		*find_blockage(t_room *start, BITFIELD_TYPE *visited, BITFIELD_TYPE *in_paths)
{
	size_t	i;
	t_room	*found;
	size_t	tried;


	i = 0;
	found = NULL;
	tried = 0;
	if (room_in_bitfield(start, in_paths) == 1)
		return (start);
	add_to_bitfield(start, visited);
	/* Shouldn't be possible to reach start */
	while (found == NULL && tried < start->neighbours_len)
	{
		if (find_most_promising(start, visited, &i) == 0)
			return (NULL);
		tried++;
		found = find_blockage(start->neighbours[i], visited, in_paths);
	}
	return (found);
}

t_room		*find_next_node(t_route *route, t_room *block)
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

ssize_t		remove_conn(t_best *state, t_room *block, t_map *map)
{
	size_t	i;
	t_room	*next;

	i = 0;
	while (i < state->used)
	{
		if (room_in_bitfield(block, state->combi[i]) == 1)
		{
			next = find_next_node(state->combi[i], block);
			if (next == NULL)
				return (EXIT_FAILURE);
			del_tube(block, next, map);
			return (EXIT_SUCCESS);
		}
		i++;
	}
}

ssize_t		remove_blockage(t_best *state, t_map *map)
{
	BITFIELD_TYPE	*in_paths;
	BITFIELD_TYPE	*visited;
	t_room			*found;
	size_t			tried;
	size_t			i;

	i = 0;
	tried = 0;
	found = NULL;
	if (setup_in_paths(state, &in_paths, map) == EXIT_FAILURE
	|| bite_alloc(&visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	add_to_bitfield(map->end, visited);
	while (found == NULL && tried < map->end->neighbours_len)
	{
		if (find_most_promising_start(map->end, visited, in_paths, &i) == 0)
			return (EXIT_NO_BLOCKS);
		tried++;
		found = find_blockage(map->end->neighbours[i], visited, in_paths);
	}
	if (found != NULL)
	{
		if (remove_conn(state, found, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
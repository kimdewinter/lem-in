/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_blockage.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 10:37:22 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/17 10:58:01 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void		find_most_promising_start(t_room *start, BITFIELD_TYPE *visited,
BITFIELD_TYPE *in_paths, ssize_t *i)
{
	ssize_t	best;
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
}

static int		find_most_promising(t_room *start, BITFIELD_TYPE *visited,
size_t *i)
{
	ssize_t	best;
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

t_room			*find_blockage(t_room *start, BITFIELD_TYPE *visited,
BITFIELD_TYPE *in_paths)
{
	size_t	i;
	t_room	*found;
	size_t	tried;

	i = 0;
	found = NULL;
	tried = 0;
	if (room_in_bitfield(start, in_paths) == 1)
		return (start);
	bite_add_room_to_bitfield(start, visited);
	while (found == NULL && tried < start->neighbours_len)
	{
		if (find_most_promising(start, visited, &i) == 0)
			return (NULL);
		tried++;
		found = find_blockage(start->neighbours[i], visited, in_paths);
	}
	return (found);
}

static ssize_t	handle_return(t_best *candidate, t_room *found, t_map *map)
{
	if (found != NULL)
	{
		if (remove_conn(candidate, found, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else
	{
		printf("NO BLOCKS\n");
		return (EXIT_NO_BLOCKS);
	}
}

ssize_t			remove_blockage(t_best *candidate, t_map *map)
{
	BITFIELD_TYPE	*visited;
	t_room			*found;
	size_t			tried;
	ssize_t			i;

	i = 0;
	tried = 0;
	found = NULL;
	printf("\nREMOVE BLOCKAGE PATHS %lu\n\n", candidate->used);
	if (bite_alloc(&visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	bite_add_room_to_bitfield(map->end, visited);
	while (found == NULL && tried < map->end->neighbours_len)
	{
		find_most_promising_start(map->end, visited, candidate->in_paths, &i);
		if (i == -1)
			return (EXIT_NO_BLOCKS);
		tried++;
		found = find_blockage(map->end->neighbours[i], visited, candidate->in_paths);
	}
	free (visited);
	return (handle_return(candidate, found, map));
}

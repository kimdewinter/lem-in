/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_combinations.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/22 16:03:32 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/01 13:24:52 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t		ft_factorial(size_t	n)
{
	if (n == 0)
		return (1);
	return (n * ft_factorial(n - 1));
}

/* N = number of paths, r is max number of parallel paths */
ssize_t		calc_combinations(const size_t n, size_t r)
{
	// (n!) / (r!(n-r)!);
	size_t	result;
	size_t	fact_n;
	size_t	i;

	result = 0;
	i = r;
	fact_n = ft_factorial(n);
	while (i > 0)
	{
		result += (fact_n / (ft_factorial(i) * ft_factorial(n - i)));
		i--;
	}
	if (result == 0)
		result = INTMAX_MAX;
	return (result);
}

void		calc_start_end(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->start->neighbours_len)
	{
		if (map->start->neighbours[i]->nb->dead_end == 0)
			map->start_live++;
		i++;
	}
	i = 0;
	while (i < map->end->neighbours_len)
	{
		if (map->end->neighbours[i]->nb->dead_end == 0)
			map->end_live++;
		i++;
	}
}

size_t		route_conflict_with_visited(t_subpath *route, BITFIELD_TYPE *visited,
t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->bitfield_len)
	{
		if ((route->bitconj[i] & visited[i]) != (BITFIELD_TYPE)0)
			return (1);
		i++;
	}
	return (0);
}

size_t		route_conflict_with_curr(t_room *conj, t_subpath *pt)
{
	if ((pt->bitconj[conj->room_i / BITFIELD_SIZE] &
	((BITFIELD_TYPE)1 << (63 - conj->room_i % BITFIELD_SIZE))) != (BITFIELD_TYPE)0)
		return (1);
	return (0);	
}

size_t		max_possible(t_map *map)
{
	size_t			max;
	BITFIELD_TYPE	*visited;
	t_room			*tmp;
	size_t			i;
	size_t			j;

	if (bite_alloc(&visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	max = map->start->num_options;
	printf("Max before %lu\n", max);
	i = 0;
	while (i < map->rooms->size)
	{
		if (map->rooms->entries[i] != NULL &&
		((t_room *)map->rooms->entries[i]->val) != map->end &&
		((t_room *)map->rooms->entries[i]->val)->dead_end == 0 &&
		((t_room *)map->rooms->entries[i]->val)->is_conj == 1 &&
		((t_room *)map->rooms->entries[i]->val)->num_options > 1)
		{
			j = 0;
			tmp = ((t_room *)map->rooms->entries[i]->val);
			while (j < map->start->num_options)
			{
				// Does route go through current junction && not through previously checked
				// ones
				if (route_conflict_with_curr(tmp, map->start->routes[j]) == 1
				&& route_conflict_with_visited(tmp->routes[j], visited, map) == 0)
					max--;
				j++;
				add_to_bitfield(((t_room *)map->rooms->entries[i]->val), visited);
			}
		}
		i++;
	}
	return (max);
	// For all conjunctions, if more than one path goes through it, 
	// subtract num options -1 from max UNLESS that same path has a conflict
	// with a conj we've already check
}

size_t		max_parallels(t_map *map)
{
	/* either number of viable routes
	number of ends
	connections to start
	connections to end */
	size_t	lowest;
	size_t	max;

	max = max_possible(map);
	printf("Max %lu\n", max);
	calc_start_end(map);
	lowest = map->start_live;
	printf("lowest %lu\n", lowest);
	printf("ants: %lu start conn %lu end conn %lu routes %lu\n", map->antmount, map->start_live,
	map->end_live, map->start->num_options);
	if (map->start->num_options < map->start_live)
		lowest = map->start->num_options;
	if (map->end_live < lowest)
		lowest = map->end_live;
	if ((size_t)map->antmount < lowest)
		lowest = map->antmount;
	// if (max < lowest)
	// 	lowest = max;
	return (lowest);
}
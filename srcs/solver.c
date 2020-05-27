/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/25 15:40:27 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/26 13:20:43 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static void		compare_solutions(t_map *map, size_t *low, t_combi **solution,
size_t i)
{
	size_t	tmp;

	tmp = calc_cost(map->antmount, map->valid_combis[i]);
	if (tmp < *low)
	{
		*low = tmp;
		*solution = map->valid_combis[i];
	}
}

size_t		solver(t_map *map)
{
	size_t	i;
	size_t	low;
	int		first;
	t_combi	*solution;

	i = 0;
	first = 1;
	solution = NULL;
	while (i < map->valid_combis)
	{
		if (map->valid_combis[i]->num_routes <= map->antmount)
		{
			if (first == 1)
			{
				low = calc_cost(map->antmount, map->valid_combis[i]);
				solution = map->valid_combis[i];
				first = 0;
			}
			else
				compare_solutions(map, &low, &solution, i);
		}
		i++;
	}
	if (solution == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

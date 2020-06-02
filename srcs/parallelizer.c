/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parallelizer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:10:41 by kim           #+#    #+#                 */
/*   Updated: 2020/06/02 14:37:59 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

ssize_t			copy_n_routes(t_route ***dst, t_route **src, const size_t n)
{
	size_t	i;

	if (src != NULL)
	{
		*dst = (t_route **)malloc(sizeof(t_route *) * n);
		if (*dst == NULL)
			return (EXIT_FAILURE);
		i = 0;
		while (i < n)
		{
			*dst[i] = src[i];
			i++;
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

size_t			is_valid_combi(t_map *map,
								BITFIELD_TYPE *rte1,
								BITFIELD_TYPE *rte2)
{
	size_t	i;

	if (map != NULL && rte1 != NULL && rte2 != NULL)
	{
		i = 0;
		while (i < map->bitfield_len)
		{
			if ((rte1[i] & rte2[i]) != (BITFIELD_TYPE)0)
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

static ssize_t	parallelize_setup(t_map *map, size_t *numtocombi)
{
	if (map != NULL && numtocombi != NULL)
	{
		*numtocombi = max_parallels(map);
		map->valid_combis_len = calc_combinations(map->num_routes, *numtocombi);
		map->valid_combis =
			(t_combi **)malloc(sizeof(t_combi) * map->valid_combis_len);
		if (map->valid_combis == NULL)
			return (EXIT_FAILURE);
		map->valid_combis_last_i = 0;
		while (map->valid_combis_last_i < map->valid_combis_len)
		{
			map->valid_combis[map->valid_combis_last_i] = NULL;
			map->valid_combis_last_i++;
		}
		map->valid_combis_last_i = 0;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

ssize_t			parallelize(t_map *map)
{
	size_t	numtocombi;

	if (map != NULL && parallelize_setup(map, &numtocombi) == EXIT_SUCCESS)
	{
		while (numtocombi > 0)
		{
			if (combinatron(map, NULL, numtocombi) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			numtocombi--;
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
/*
** the combinatron function and it's children could be safer,
** but it'd cost performance
** should we obsessively check parameters like Kim usually does, or not?
*/

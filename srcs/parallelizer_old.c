/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parallelizer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:10:41 by kim           #+#    #+#                 */
/*   Updated: 2020/07/06 15:41:58 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t			copy_n_routes(t_route ***dst, t_route **src, const size_t n)
{
	size_t	i;

	*dst = (t_route **)malloc(sizeof(t_route *) * n);
	if (*dst == NULL)
		return (handle_err_para(1, "copy_n_routes\n"));
	i = 0;
	while (i < n - 1)
	{
		(*dst)[i] = src[i];
		i++;
	}
	return (EXIT_SUCCESS);
}

size_t			is_valid_combi(size_t bitfield_len,
								BITFIELD_TYPE *rte1,
								BITFIELD_TYPE *rte2)
{
	size_t	i;

	i = 0;
	while (i < bitfield_len)
	{
		if ((rte1[i] & rte2[i]) != (BITFIELD_TYPE)0)
			return (0);
		i++;
	}
	return (1);
}

static ssize_t	parallelize_setup(t_map *map, size_t *numtocombi)
{
	size_t	i;

	*numtocombi = max_parallels(map);
	map->solution.combi =
		(t_route **)malloc(sizeof(t_route *) * *numtocombi);
	if (map->solution.combi == NULL)
		return (handle_err_para(1, "parallelize_setup\n"));
	map->solution.len = *numtocombi;
	i = 0;
	while (i < *numtocombi)
	{
		map->solution.combi[i] = NULL;
		i++;
	}
	map->solution.used = 0;
	map->solution.turns = 0;
	return (EXIT_SUCCESS);
}

ssize_t			parallelize(t_map *map)
{
	size_t	numtocombi;

	if (map == NULL)
		return (handle_err_para(2, NULL));
	if (parallelize_setup(map, &numtocombi) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	while (numtocombi > 0)
	{
		if (combinatron(map, NULL, numtocombi) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		numtocombi--;
	}
	return (EXIT_SUCCESS);
}
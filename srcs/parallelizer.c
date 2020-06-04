/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parallelizer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:10:41 by kim           #+#    #+#                 */
/*   Updated: 2020/06/03 16:36:02 by kim           ########   odam.nl         */
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
	size_t	i;

	*numtocombi = max_parallels(map);//Should we check if this is above 0?
	map->best_combi = (t_route **)malloc(sizeof(t_route *) * map->num_routes);
	if (map->best_combi == NULL)
		return (handle_err_para(1, "parallelize_setup\n"));
	map->best_combi_len = map->num_routes;
	i = 0;
	while (i < map->num_routes)
	{
		map->best_combi[i] = NULL;
		i++;
	}
	map->best_combi_used = 0;
	map->best_combi_turns = 0;
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

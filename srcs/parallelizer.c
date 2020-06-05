/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parallelizer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:10:41 by kim           #+#    #+#                 */
/*   Updated: 2020/06/05 14:25:28 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

ssize_t			copy_n_routes(t_route ***dst, t_route **src, const size_t n)
{
	size_t	i;

	*dst = (t_route **)malloc(sizeof(t_route *) * n);
	if (*dst == NULL)
		return (handle_err_para(1, "copy_n_routes\n"));
	i = 0;
	while (i < n)
	{
		*dst[i] = src[i];
		i++;
	}
	return (EXIT_SUCCESS);
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

	*numtocombi = max_parallels(map);
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

	printf("In parallelize\n");
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
	printf("parallelize exit succes\n");
	for (size_t i = 0; i < map->best_combi_used; i++)
	{
		for (size_t j = 0; j < map->best_combi[i]->len; j++)
			printf("%s ", map->best_combi[i]->route[j]->name);
		printf("\n");	
	}
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parallelizer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:10:41 by kim           #+#    #+#                 */
/*   Updated: 2020/05/26 14:23:58 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static ssize_t	combinatron_setup_begin(t_map *map,
										t_poscom *child,
										const size_t rtes_to_combi)
{
	size_t	i;

	if (map != NULL && child != NULL && rtes_to_combi > 0)
	{
		child->routes = (t_route **)malloc(sizeof(t_route *) * rtes_to_combi);
		if (child->routes == NULL)
			return (EXIT_FAILURE);
		i = 0;
		while (i < rtes_to_combi)
		{
			child->routes[i] = NULL;
			i++;
		}
		if (bite_alloc(&(child->bitroutes), map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		child->i = 0;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);	
}

static ssize_t	combinatron_setup(t_map *map,
									const t_poscom *parent,
									t_poscom *child,
									const size_t rtes_to_combi)
{
	if (map != NULL && child != NULL && rtes_to_combi > 0)
	{
		if (parent == NULL)
			return (combinatron_setup_begin(map, child, rtes_to_combi));
		child->i = parent->i + 1;
		if (child->i >= map->num_routes)
			return (EXIT_FAILURE);
		if (bite_alloc_noval(&(child->bitroutes), map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (bite_bitroute_merge(&(child->bitroutes), parent->bitroutes,
			map->routes[child->i], map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (copy_routes(parent->routes, child->routes, rtes_to_combi) ==
			EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);	
}

static ssize_t	combinatron(t_map *map,
							const t_poscom *parent,
							const size_t rtes_to_combi)
{
	t_poscom	child;

	if (map != NULL && rtes_to_combi > 0 && combinatron_setup(
		map, parent, &child, rtes_to_combi) == EXIT_SUCCESS)
	{

	}
	return (EXIT_FAILURE);
}

ssize_t			parallelize(t_map *map)
{
	size_t	num_to_combi;

	if (map != NULL)
	{
		map->valid_combis_len = 0;//TO DO: function that calculates this
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
		num_to_combi = 1;
		while (num_to_combi < map->num_routes)
		{
			//if (combinatron(map) == EXIT_FAILURE)
				//return (EXIT_FAILURE);
			num_to_combi++;
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
/*
** the combinatron function and it's children could be safer, but it'd cost performance
** should we obsessively check parameters like Kim usually does, or not?
*/
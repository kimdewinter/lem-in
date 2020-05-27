/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parallelizer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:10:41 by kim           #+#    #+#                 */
/*   Updated: 2020/05/27 15:46:45 by kim           ########   odam.nl         */
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
		child->num_routes = 0;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);	
}

static ssize_t	copy_n_routes(t_route **dst, t_route **src, const size_t n)
{
	size_t	i;

	if (src != NULL)
	{
		dst = (t_route **)malloc(sizeof(t_route *) * n);
		if (dst == NULL)
			return (EXIT_FAILURE);
		i = 0;
		while (i < n)
		{
			dst[i] = src[i];
			i++;
		}
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
		child->i = parent->i;
		if (child->i >= map->num_routes)
			return (EXIT_FAILURE);
		if (bite_alloc_noval(&(child->bitroutes), map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (bite_bitroute_merge(child->bitroutes, parent->bitroutes,
			map->routes[parent->i]->bitroute, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (copy_n_routes(child->routes, parent->routes, rtes_to_combi) ==
			EXIT_FAILURE)
			return (EXIT_FAILURE);
		child->routes[parent->num_routes] = map->routes[child->i];
		child->num_routes = parent->num_routes + 1;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);	
}

static size_t	is_valid_combi(t_map *map,
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

static ssize_t	combinatron_cleanup(t_map *map, t_poscom *combi, ssize_t ret_val)
{
	if (map != NULL && combi != NULL)
	{
		if (combi->routes != NULL)
		{
			free(combi->routes);
			combi->routes = NULL;
		}
		if (combi->bitroutes != NULL)
		{
			free(combi->bitroutes);
			combi->bitroutes = NULL;
		}
		return (ret_val);
	}
	return (EXIT_FAILURE);
}

static ssize_t	combinatron_commit_combi(t_map *map, const t_poscom *combi)
{
	t_combi	*new;

	if (map != NULL && combi != NULL && combi->routes != NULL &&
		combi->bitroutes != NULL &&
		map->valid_combis_last_i < map->valid_combis_len)
	{
		map->valid_combis[map->valid_combis_last_i] =
			(t_combi *)malloc(sizeof(t_combi) * 1);
		new = map->valid_combis[map->valid_combis_last_i];
		if (new == NULL)
			return (EXIT_FAILURE);
		new->routes =
			(t_route **)malloc(sizeof(t_route *) * combi->num_routes);
		if (new->routes == NULL || copy_n_routes(
			new->routes, combi->routes, combi->num_routes) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (bite_alloc_noval(&(new->bitroutes), map) == EXIT_FAILURE ||
			bite_bitroute_copy(new->bitroutes, combi->bitroutes, map) ==
			EXIT_FAILURE)
			return (EXIT_FAILURE);
		map->valid_combis_last_i++;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static ssize_t	combinatron(t_map *map,
							const t_poscom *parent,
							const size_t rtes_to_combi)
{
	t_poscom	child;

	if (map != NULL && rtes_to_combi > 0 &&
		combinatron_setup(map, parent, &child, rtes_to_combi) == EXIT_SUCCESS)
	{
		if (child.num_routes == rtes_to_combi)
		{
			if (combinatron_commit_combi(map, &child) == EXIT_FAILURE)
				return (combinatron_cleanup(map, &child, EXIT_FAILURE));
		}
		else
		{
			while (child.i < map->num_routes - (rtes_to_combi - child.num_routes))
			{
				if (is_valid_combi(map, child.bitroutes, map->routes[child.i]->bitroute) == 1)
					if (combinatron(map, &child, rtes_to_combi) == EXIT_FAILURE)
						return (combinatron_cleanup(map, &child, EXIT_FAILURE));
				child.i++;
			}
		}
		return (combinatron_cleanup(map, &child, EXIT_SUCCESS));
	}
	return (combinatron_cleanup(map, &child, EXIT_FAILURE));
}

ssize_t			parallelize(t_map *map)
{
	size_t	num_to_combi;

	if (map != NULL)
	{
		num_to_combi = max_parallels(map);
		map->valid_combis_len = calc_combinations(map->num_routes, num_to_combi);
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
		while (num_to_combi > 0)
		{
			if (combinatron(map, NULL, num_to_combi) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			num_to_combi--;
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}//TO DO: make it never search for more parallels than there are ways in/out of start/end room(lowest)
/*
** the combinatron function and it's children could be safer, but it'd cost performance
** should we obsessively check parameters like Kim usually does, or not?
*/

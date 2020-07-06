/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   combinatron.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 14:00:07 by kim           #+#    #+#                 */
/*   Updated: 2020/07/06 15:41:37 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	combinatron_cleanup(t_map *map,
									t_poscom *combi,
									ssize_t ret_val)
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

static ssize_t	combinatron_commit_combi(t_map *map, const t_poscom *candidate)
{
	size_t	i;
	size_t	candidate_turns;

	i = 0;
	candidate_turns = calc_cost(map->antmount, candidate);
	if (candidate_turns < map->solution.turns || (candidate_turns ==
		map->solution.turns && candidate->num_routes < map->solution.len) ||
		map->solution.used == 0)
	{
		while (i < candidate->num_routes)
		{
			if (i >= map->solution.len)
				return (handle_err_comtron(2, "combinatron_commit_combi\n"));
			map->solution.combi[i] = candidate->routes[i];
			i++;
		}
		while (i < map->solution.used)
		{
			if (i >= map->solution.len)
				return (handle_err_comtron(2, "combinatron_commit_combi\n"));
			map->solution.combi[i] = NULL;
			i++;
		}
		map->solution.used = candidate->num_routes;
		map->solution.turns = candidate_turns;
	}
	return (EXIT_SUCCESS);
}

static ssize_t	combinatron_setup_begin(t_map *map,
										t_poscom *child,
										const size_t rtes_to_combi)
{
	size_t	i;

	child->routes = (t_route **)malloc(sizeof(t_route *) * rtes_to_combi);
	if (child->routes == NULL)
		return (handle_err_comtron(1, "combinatron_setup_begin\n"));
	i = 0;
	while (i < rtes_to_combi)
	{
		child->routes[i] = NULL;
		i++;
	}
	if (bite_alloc(&(child->bitroutes), map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	child->i = 0;
	child->num_routes = 0;
	return (EXIT_SUCCESS);
}

static ssize_t	combinatron_setup(t_map *map,
									const t_poscom *parent,
									t_poscom *child,
									const size_t rtes_to_combi)
{
	if (parent == NULL)
		return (combinatron_setup_begin(map, child, rtes_to_combi));
	child->num_routes = parent->num_routes + 1;
	if (bite_alloc_noval(&(child->bitroutes), map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (bite_bitroute_merge(child->bitroutes, parent->bitroutes,
		map->routes[parent->i]->bitroute, map) != EXIT_SUCCESS)
		return (handle_err_comtron(0, "combinatron_setup\n"));
	if (copy_n_routes(&(child->routes), parent->routes, parent->num_routes + 1)
		!= EXIT_SUCCESS)
		return (EXIT_FAILURE);
	child->routes[parent->num_routes] = map->routes[parent->i];
	child->i = parent->i + 1;
	return (EXIT_SUCCESS);
}

ssize_t			combinatron(t_map *map,
							const t_poscom *parent,
							const size_t rtes_to_combi)
{
	t_poscom	child;

	if (combinatron_setup(map, parent, &child, rtes_to_combi) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (child.num_routes == rtes_to_combi)
	{
		if (combinatron_commit_combi(map, &child) == EXIT_FAILURE)
			return (combinatron_cleanup(map, &child, EXIT_FAILURE));
	}
	else
	{
		while (child.i <= map->num_routes - (rtes_to_combi - child.num_routes))
		{
			if (is_valid_combi(map->bitfield_len,
				child.bitroutes, map->routes[child.i]->bitroute) == 1)
				if (combinatron(map, &child, rtes_to_combi) == EXIT_FAILURE)
					return (combinatron_cleanup(map, &child, EXIT_FAILURE));
			child.i++;
		}
	}
	return (combinatron_cleanup(map, &child, EXIT_SUCCESS));
}

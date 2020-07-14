/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   combinatron.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 15:19:04 by kim           #+#    #+#                 */
/*   Updated: 2020/07/14 16:00:16 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t			commit_best(const t_poscom *bestcom, t_best *new_entry)
{
	if (bestcom == NULL)
		return (EXIT_FAILURE);
	new_entry->len = bestcom->num_routes;
	new_entry->combi =
		(t_route **)malloc(sizeof(t_route *) * new_entry->len);
	if (new_entry->combi == NULL)
		return (handle_err_comtron(1, "commit_best\n"));
	new_entry->used = 0;
	while (new_entry->used < bestcom->num_routes)
	{
		new_entry->combi[new_entry->used] = bestcom->routes[new_entry->used];
		new_entry->used++;
	}
	new_entry->turns = bestcom->turns;
	return (EXIT_SUCCESS);
}

static size_t	is_valid_combi(size_t bitfield_len,
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

static ssize_t	commit_multi_route_com(t_poscom **new_entry,
												const t_poscom *rootcom,
												const size_t i,
												const t_map *map)
{
	size_t	j;

	*new_entry = (t_poscom *)malloc(sizeof(t_poscom) * 1);
	if (*new_entry == NULL)
		return (handle_err_comtron(1, "commit_multi_route_com\n"));
	(*new_entry)->num_routes = rootcom->num_routes + 1;
	if (bite_bitroute_merge(&(*new_entry)->bitroutes, rootcom->bitroutes,
		map->routes[i]->bitroute, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	(*new_entry)->map_routes_i = i;
	(*new_entry)->routes =
		(t_route **)malloc(sizeof(t_route *) * (*new_entry)->num_routes);
	if ((*new_entry)->routes == NULL)
		return (handle_err_comtron(1, "commit_multi_route_com\n"));
	j = 0;
	while (j < rootcom->num_routes)
	{
		(*new_entry)->routes[j] = rootcom->routes[j];
		j++;
	}
	(*new_entry)->routes[j] = map->routes[i];
	(*new_entry)->turns = calc_cost(map->antmount, *new_entry);
	return (EXIT_SUCCESS);
}

static ssize_t	combinatron(const t_poscom *rootcom,
									t_comvault *current,
									t_poscom **bestcom,
									const t_map *map)
{
	size_t	i;

	i = rootcom->map_routes_i + 1;
	while (i < map->num_routes)
	{
		if (is_valid_combi(map->bitfield_len, map->routes[i]->bitroute,
			rootcom->bitroutes) == 1)
		{
			if (current->coms_used >= current->coms_len &&
				expand_comvault(current) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (commit_multi_route_com(&current->coms[current->coms_used],
				rootcom, i, map) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (current->coms[current->coms_used]->turns <
				(*bestcom)->turns)
				*bestcom = current->coms[current->coms_used];
			current->coms_used++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

ssize_t			parallelize_multiples_of(const t_comvault *previous,
									t_comvault *current,
									t_poscom **bestcom,
									const t_map *map)
{
	size_t	i;

	i = 0;
	while (i < previous->coms_used)
	{
		if (combinatron(previous->coms[i], current, bestcom, map) ==
			EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

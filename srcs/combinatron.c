/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   combinatron.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 15:19:04 by kim           #+#    #+#                 */
/*   Updated: 2020/07/09 16:44:44 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

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

static ssize_t			commit_multi_route_com(t_poscom **new_entry,
												const t_poscom *rootcom,
												const size_t i,
												const t_map *map)
{
	size_t	j;

	*new_entry = (t_poscom *)malloc(sizeof(t_poscom) * 1);
	if (*new_entry == NULL)
		return (EXIT_FAILURE);
	(*new_entry)->num_routes = rootcom->num_routes + 1;
	if (bite_bitroute_merge(&(*new_entry)->bitroutes, rootcom->bitroutes,
		map->routes[i]->bitroute, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	(*new_entry)->map_routes_i = i;
	(*new_entry)->routes =
		(t_route **)malloc(sizeof(t_route *) * (*new_entry)->num_routes);
	if ((*new_entry)->routes == NULL)
		return (EXIT_FAILURE);
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

static ssize_t			combinatron(t_comvault *current,
									const t_poscom *rootcom,
									t_poscom **bestcom,
									const t_map *map)
{
	size_t	i;

	i = rootcom->map_routes_i + 1;
	while (i < map->num_routes)
	{
		if (is_valid_combi(
			BITFIELD_SIZE, map->routes[i]->bitroute, rootcom->bitroutes) == 1)
		{
			if (commit_multi_route_com(&current->coms[current->coms_used],
				rootcom, i, map) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			current->coms_used++;
			if (current->coms[current->coms_used - 1]->turns <
				(*bestcom)->turns)
				*bestcom = current->coms[current->coms_used - 1];
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

ssize_t	parallelize_multiples_of(const t_comvault *previous,
									t_comvault *current,
									t_poscom **bestcom,
									const t_map *map)
{
	size_t	i;

	i = 0;
	while (i < previous->coms_used)
	{
		if (combinatron(current, previous->coms[i], bestcom, map) ==
			EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

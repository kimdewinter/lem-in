/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   combinatron.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 15:19:04 by kim           #+#    #+#                 */
/*   Updated: 2020/07/09 13:45:49 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"


/*static ssize_t	combinatron_singles(t_comvault *valcoms,
									t_poscom *bestcom,
									const t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->num_routes && i < valcoms->coms_len)
	{
		valcoms->coms[i]->routes = (t_route **)malloc(sizeof(t_route *) * 1);
		if (valcoms->coms[i]->routes == NULL)
			return (EXIT_FAILURE);
		
		valcoms->coms[i]->routes[0] = map->routes[i];
		valcoms->coms[i]->num_routes = 1;
		i++;
	}
}

ssize_t			combinatron(t_comvault *valcoms,
							t_poscom *bestcom,
							const t_map *map)
{
	if (valcoms->coms_of_num == 1)
		if (combinatron_singles(valcoms, bestcom, map) == EXIT_FAILURE);
			return (EXIT_FAILURE);
}*/

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

static ssize_t	commit_singleton(t_comvault *valcoms,
									t_poscom *bestcom,
									const size_t i,
									const t_map *map)
{
	valcoms->coms[i] = (t_poscom *)malloc(sizeof(t_poscom) * 1);
	if (valcoms->coms[i] == NULL)
		return (EXIT_FAILURE);
	valcoms->coms[i]->routes =
		(t_route **)malloc(sizeof(t_route *) * valcoms->coms_of_num);
	if (valcoms->coms[i]->routes == NULL)
		return (EXIT_FAILURE);
	valcoms->coms[i]->routes[0] = map->routes[i];
	valcoms->coms[i]->num_routes = valcoms->coms_of_num;
	valcoms->coms[i]->bitroutes = map->routes[i]->bitroute;
	valcoms->coms[i]->turns = calc_cost(map->antmount, valcoms->coms[i]);
	if (bestcom == NULL || valcoms->coms[i]->turns < bestcom->turns)
		bestcom = valcoms->coms[i];
}

ssize_t			combinatron(t_comvault *valcoms,
							t_poscom *bestcom,
							const t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->num_routes && i < valcoms->coms_len)
	{
		if (valcoms->coms_of_num == 1)
		{
			if (commit_singleton(valcoms, bestcom, i, map) == EXIT_FAILURE);
				return (EXIT_FAILURE);
		}
		else if (is_valid_combi(BITFIELD_SIZE, valcoms->coms[i]->bitroutes,
								map->routes[i]->bitroute) == EXIT_FAILURE)
		{
			return (EXIT_FAILURE);
		}
		i++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parallelizer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 13:43:45 by kim           #+#    #+#                 */
/*   Updated: 2020/07/15 17:18:37 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	commit_single_route_com(t_poscom **new_entry,
										const size_t i,
										const t_map *map)
{
	*new_entry = (t_poscom *)malloc(sizeof(t_poscom) * 1);
	if (*new_entry == NULL)
		return (handle_err_para(1, "commit_single_route_com\n"));
	(*new_entry)->routes =
		(t_route **)malloc(sizeof(t_route *) * 1);
	if ((*new_entry)->routes == NULL)
		return (handle_err_para(1, "commit_single_route_com\n"));
	(*new_entry)->routes[0] = map->routes[i];
	(*new_entry)->num_routes = 1;
	(*new_entry)->bitroutes = map->routes[i]->bitroute;
	(*new_entry)->map_routes_i = i;
	(*new_entry)->turns = calc_cost(map->antmount, (*new_entry));
	return (EXIT_SUCCESS);
}

static ssize_t	parallelize_singles(t_comvault *valcoms,
									t_poscom **bestcom,
									const t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->num_routes)
	{
		if (commit_single_route_com(&valcoms->coms[i], i, map) ==
			EXIT_FAILURE)
			return (EXIT_FAILURE);
		valcoms->coms_used++;
		if (*bestcom == NULL || valcoms->coms[i]->turns < (*bestcom)->turns)
			*bestcom = valcoms->coms[i];
		i++;
	}
	return (EXIT_SUCCESS);
}

static ssize_t	setup_single_comvault(t_comvault **comvault,
	const size_t coms_of_num,
	const t_map *map)
{
	size_t	i;

	*comvault = (t_comvault *)malloc(sizeof(t_comvault) * 1);
	if (*comvault == NULL)
		return (handle_err_para(1, "setup_single_comvault\n"));
	(*comvault)->coms_of_num = coms_of_num;
	(*comvault)->coms_len = (COMVAULT_LEN_INIT < map->num_routes) ?
		map->num_routes : COMVAULT_LEN_INIT;
	(*comvault)->coms_used = 0;
	(*comvault)->coms =
		(t_poscom **)malloc(sizeof(t_poscom *) * (*comvault)->coms_len);
	if ((*comvault)->coms == NULL)
		return (handle_err_para(1, "setup_single_comvault\n"));
	i = 0;
	while (i < (*comvault)->coms_len)
	{
		(*comvault)->coms[i] = NULL;
		i++;
	}
	return (EXIT_SUCCESS);
}

/*
** it's advisable not to let the comvault->coms_len get larger than 9999999
*/

static ssize_t	setup_parallelizer(size_t *maxparallels,
									t_comvault ***valcoms,
									t_poscom **bestcom,
									const t_map *map)
{
	size_t	i;

	if (max_parallels(maxparallels, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*valcoms = (t_comvault **)malloc(sizeof(t_comvault *) * *maxparallels);
	if (*valcoms == NULL)
		return (handle_err_para(1, "setup_parallelizer\n"));
	i = 0;
	while (i < *maxparallels)
	{
		if (setup_single_comvault(&(*valcoms)[i], i + 1, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	*bestcom = NULL;
	return (EXIT_SUCCESS);
}

ssize_t			parallelize(t_map *map)
{
	size_t		maxparallels;
	t_comvault	**valcoms;
	t_poscom	*bestcom;
	size_t		i;

	if (map == NULL || setup_parallelizer(
		&maxparallels, &valcoms, &bestcom, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parallelize_singles(valcoms[0], &bestcom, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = 1;
	while (i < maxparallels)
	{
		if (parallelize_multiples_of(
			valcoms[i - 1], valcoms[i], &bestcom, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	if (commit_best(bestcom, &map->solution) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	delete_all_comvaults(valcoms, maxparallels);
	free(valcoms);
	valcoms = NULL;
	return (EXIT_SUCCESS);
}

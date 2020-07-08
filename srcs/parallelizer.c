/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parallelizer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 13:43:45 by kim           #+#    #+#                 */
/*   Updated: 2020/07/08 13:18:36 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	setup_single_comvault(t_comvault *comvault,
								const size_t coms_of_num,
								const t_map *map)
{
	size_t	i;

	comvault->coms_of_num = coms_of_num;
	calc_combinations(&comvault->coms_len, map->num_routes, coms_of_num);
	comvault->coms_used = 0;
	comvault->coms =
		(t_poscom **)malloc(sizeof(t_poscom *) * comvault->coms_len);
	if (comvault->coms == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < comvault->coms_len)
	{
		comvault->coms[i] = NULL;
		i++;
	}
	return (EXIT_SUCCESS);
}

static ssize_t	setup_parallelizer(size_t *maxparallels,
									t_comvault ***valcoms,
									t_poscom **bestcom,
									const t_map *map)
{
	size_t	i;

	*maxparallels = max_parallels(map);
	*valcoms = (t_comvault **)malloc(sizeof(t_comvault *) * *maxparallels);
	if (*valcoms == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < *maxparallels)
	{
		if (setup_single_comvault(*valcoms[i], i + 1, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	*bestcom = NULL;
	return (EXIT_SUCCESS);
}

ssize_t			parallelize(const t_map *map)
{
	size_t		maxparallels;
	t_comvault	**valcoms;
	t_poscom	*bestcom;

	if (map == NULL || setup_parallelizer(
		&maxparallels, &valcoms, &bestcom, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

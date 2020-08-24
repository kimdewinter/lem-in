/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_map.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 16:21:12 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/24 16:46:53 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		delete_paths(t_route ***combi, size_t num_routes)
{
	size_t	i;

	i = 0;
	while (i < num_routes)
	{
		free((*combi)[i]->route);
		(*combi)[i]->route = NULL;
		free((*combi)[i]->bitroute);
		(*combi)[i]->bitroute = NULL;
		free((*combi)[i]);
		(*combi)[i] = NULL;
		i++;
	}
	free(*combi);
	*combi = NULL;
}

void		delete_solution(t_best *solution)
{
	if (solution->combi != NULL)
		delete_paths(&solution->combi, solution->used);
	if (solution->in_paths != NULL)
	{
		free(solution->in_paths);
		solution->in_paths = NULL;
	}
}

void		delete_map(t_map *map)
{
	delete_solution(&map->solution);
	if (map->rooms != NULL)
	{
		delete_all_rooms(map->rooms);
		delete_ht(map->rooms);
	}
}
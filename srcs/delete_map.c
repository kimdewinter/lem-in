/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_map.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 14:12:09 by kim           #+#    #+#                 */
/*   Updated: 2020/06/30 14:46:26 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void	delete_solution(t_map *map)
{
	size_t	i;

	if (map->solution.combi != NULL)
	{
		i = 0;
		while (i < map->solution.len)
		{
			map->solution.combi[i] = NULL;
			i++;
		}
		free(map->solution.combi);
		map->solution.combi = NULL;
	}
	map->solution.used = 0;
	map->solution.len = 0;
	map->solution.turns = 0;
}

void		delete_map(t_map *map)
{
	map->antmount = -1;
	map->start = NULL;
	map->end = NULL;
	//PLACEHOLDER: the inside of rooms must be cleaned before the delete_ht call
	if (map->rooms != NULL)
		delete_ht(map->rooms);
	map->rooms = NULL;
	if (map->routes != NULL)
		delete_all_routes(map);
	map->num_routes = 0;
	map->bitfield_len = 0;
	delete_solution(map);
}
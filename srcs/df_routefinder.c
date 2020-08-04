/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   df_routefinder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 15:49:14 by kim           #+#    #+#                 */
/*   Updated: 2020/08/04 16:14:12 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	setup_best(t_map *map)
{
	size_t	i;

	map->solution.len = (map->start->neighbours_len < map->end->neighbours_len)
		? map->start->neighbours_len : map->end->neighbours_len;
	map->solution.combi =
		(t_route **)malloc(sizeof(t_route *) * map->solution.len);
	if (map->solution.combi == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < map->solution.len)
	{
		map->solution.combi[i] = NULL;
		i++;
	}
	map->solution.used = 0;
	map->solution.turns = 0;
	return (EXIT_SUCCESS);
}

ssize_t			find_routes_df(t_room *room_to_begin_from,
								t_map *map)
{
	BITFIELD_TYPE	*visited;

	if (setup_best(map) == EXIT_FAILURE ||
		bite_alloc(&visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	(void)room_to_begin_from;
	return (EXIT_SUCCESS);
}
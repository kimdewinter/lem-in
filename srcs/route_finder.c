/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 14:33:23 by kim           #+#    #+#                 */
/*   Updated: 2020/08/11 13:18:36 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"



ssize_t			find_routes(t_map *map)
{
	t_best	state;

	if (map->start == NULL)
		return (EXIT_FAILURE);
	if (traverse_bf(map->end, LVL_GRPH_E2S) == EXIT_FAILURE)//step 1: create level graph from end to start
		return (EXIT_FAILURE);
	if (find_routes_df(&state, map) == EXIT_FAILURE)//step 2: DFS for valid parallel routes
		return (EXIT_FAILURE);
	if (traverse_bf(map->start, LVL_GRPH_S2E) == EXIT_FAILURE)//step 3: level graph start to end
		return (EXIT_FAILURE);
	//PLACEHOLDER: check whether state is now better than the previous map->solution, replace if needed
	// print_rooms(map->rooms);
	print_best(&state);
	exit (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

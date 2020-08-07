/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 14:33:23 by kim           #+#    #+#                 */
/*   Updated: 2020/08/01 16:48:35 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"



ssize_t			find_routes(t_map *map)
{
	int			flow;
	// t_config	*curr;

	flow = -1;
	/* Give it a bitfield to know when to stop assigning weights from start */
	if (set_weights(map, flow) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// find_shortest_path_config(&curr, map);
	print_map(map);
	exit (0);
	// while (configuration_found == 1)
	// {
	// 	/* Set weights in appropriate direction
	// 	DFS shortest path
	// 	Set weights in opposite direction
	// 	Find blocking node and remove
	// 	Find paths
	// 	*/
	// }
	if (map->start == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

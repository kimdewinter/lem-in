/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sanitize_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 16:41:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/06 16:59:57 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

/* Needs checking:
	Is there a start room
	Is there an end room
*/

int		sanitize_input(t_map *map)
{
	t_room *tmp;

	if (map->rooms = NULL)
		return (ft_error("No rooms provided\n", EXIT_FAILURE));
	if (map->start == NULL)
		return (ft_error("No start room provided\n", EXIT_FAILURE));
	if (map->end == NULL)
		return (ft_error("No end room provided\n", EXIT_FAILURE));	
	tmp = (t_room *)search_ht(map->rooms, map->start);
	if (tmp->neighbours == NULL)
		return (ft_error("No path from start room\n", EXIT_FAILURE));
	tmp = (t_room *)search_ht(map->rooms, map->end);
	if (tmp->neighbours == NULL)
		return (ft_error("No path from end room\n", EXIT_FAILURE));
}
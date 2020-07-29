/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bfs.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 13:37:28 by kim           #+#    #+#                 */
/*   Updated: 2020/07/29 14:05:53 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	grow_route(t_bfs_route *route, BITFIELD_TYPE *visited)
{

}

ssize_t			bfs_shortest(t_map *map)
{
	BITFIELD_TYPE	*visited;
	t_bfs_route		bfs_routes;

	if (allocopy_bitfield(&visited, map->start->bitroom, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);

}
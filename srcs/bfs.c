/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bfs.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 13:37:28 by kim           #+#    #+#                 */
/*   Updated: 2020/07/29 14:35:56 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	grow_route(t_bfs_route *route,
							t_bfs_vault *vault,
							BITFIELD_TYPE *visited)
{
	size_t	i;

	i = 0;
}

ssize_t			bfs_shortest(t_map *map)
{
	t_bfs_vault	vault;

	if (bite_bitroute_copy(vault.visited, map->start->bitroom, map) ==
			EXIT_FAILURE)
		return (EXIT_FAILURE);

}
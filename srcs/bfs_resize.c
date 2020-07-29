/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bfs_resize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 15:01:12 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/29 15:01:12 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t		increase_route_size(t_bfs_route *bfs_route)
{
	size_t	new_size;
	t_room	**new_route;
	size_t	i;

	i = 0;
	new_size = bfs_route->len * 2;
	new_route = create_new_route(new_size);
	if (new_route)
	{
		while (i < bfs_route->used)
		{
			new_route[i] = bfs_route->route[i];
			i++;
		}
		bfs_route->len = new_size;
		free (bfs_route->route);
		bfs_route->route = new_route;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

ssize_t		increase_vault_size(t_bfs_vault *bfs_vault)
{

}
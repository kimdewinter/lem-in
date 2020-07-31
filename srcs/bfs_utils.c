/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bfs_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 13:37:28 by kim           #+#    #+#                 */
/*   Updated: 2020/07/31 14:55:52 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_room      		**create_new_route(size_t size)
{
    t_room        **new;

    new = (t_room **)malloc(sizeof(t_room *) * size);
    return (new);
}

static void         copy_bfs_route(const t_bfs_route *parent, t_bfs_route *new)
{
    size_t	i;

	i = 0;
	while (i < parent->used)
	{
		new->route[i] = parent->route[i];
		i++;
	}
	new->used = parent->used;
}

static t_bfs_route        *create_bfs_route(const t_bfs_route *parent,
t_room *next_to_add, const t_map *map)
{
    t_bfs_route *new;
	size_t		size;

	if (parent == NULL)
	{
		size = (map->rooms->count * 100) / ((100 / INIT_ROUTE_PERC) * 100);
		if (size == 0)
			size = map->rooms->count;
	}
	else
		size = parent->len;
    new = (t_bfs_route *)malloc(sizeof(t_bfs_route));
    if (new)
    {
        new->route = create_new_route(size);
        if (new->route)
        {
			new->len = size;
    		new->used = 0;
            new->next_to_add = next_to_add;
            if (parent != NULL)
                copy_bfs_route(parent, new);
			return (new);
        }
    }
    return (NULL);
}

ssize_t	add_bfs_room(t_bfs_route *bfs_route, t_room *to_add)
{
	if (bfs_route->used == bfs_route->len)
	{
		if (increase_route_size(bfs_route) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	bfs_route->route[bfs_route->used] = to_add;
	bfs_route->used++;
	return (EXIT_SUCCESS);
}

static ssize_t	add_to_vault(t_bfs_vault *vault, t_bfs_route *new, const t_map *map)
{
	if (vault->used == vault->len)
	{
		if (increase_vault_size(vault, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	vault->routes[vault->used] = new;
	vault->used++;
	return (EXIT_SUCCESS);
}

ssize_t  branch_bfs_route(const t_bfs_route *parent,
							t_bfs_vault *vault,
							t_room *next_to_add,
							const t_map *map)
{
    t_bfs_route *new;

    new = create_bfs_route(parent, next_to_add, map);
	if (new != NULL)
		return (add_to_vault(vault, new, map));
	return (EXIT_FAILURE);
}

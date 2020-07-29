/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bfs_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 13:37:28 by kim           #+#    #+#                 */
/*   Updated: 2020/07/29 14:35:35 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_room             **create_new_route(t_map *map, t_bfs_route *bfs_route)
{
    size_t        size;
    t_room        **new;

    size = (map->rooms->count * 100) / ((100 / INIT_ROUTE_PERC) * 100);
    if (size == 0)
        size = map->rooms->count;
    new->len = size;
    new->used = 0;
    new = (t_room **)malloc(sizeof(t_room *) * size);
    return (new);
}

t_bfs_route        *create_bfs_route(t_map *map)
{
    t_bfs_route *new;

    new = (t_bfs_route *)malloc(sizeof(t_bfs_route));
    if (new)
    {
        new->next_to_add = NULL;
        new->route = NULL;
        new->len = 
        if (new->route != NULL)
            return (new);
    }
    return (NULL);
}

static ssize_t    add_to_route(t_bfs_route *route, t_room *to_add)
{
    if (route->used == len)
    {
        if (increase_route_size())
    }
}

t_bfs_route        *setup_bfs_route(t_room *src, t_room *dst, t_map *map)
{
    t_bfs_route    *new;

    new = create_bfs_route(map);
    if (new)
    {
        if (add_to_route(new, src) == EXIT_FAILURE)
        {
            free (new->route);
            free (new);
            return (NULL);
        }
    }
}

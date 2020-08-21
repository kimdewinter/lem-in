/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   df_routefinder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 15:49:14 by kim           #+#    #+#                 */
/*   Updated: 2020/08/21 16:25:23 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	setup_best(t_best *best, const t_map *map)
{
	size_t	i;

	best->len = (map->start->neighbours_len < map->end->neighbours_len)
		? map->start->neighbours_len : map->end->neighbours_len;
	best->combi =
		(t_route **)malloc(sizeof(t_route *) * best->len);
	if (best->combi == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < best->len)
	{
		best->combi[i] = NULL;
		i++;
	}
	best->used = 0;
	best->turns = 0;
	return (EXIT_SUCCESS);
}

static ssize_t	setup_dfs_wrap(t_dfs_wrap *wrap,
								t_best *candidate,
								const t_map *map)
{
	if (wrap == NULL ||
		bite_alloc(&wrap->visited, map) == EXIT_FAILURE ||
		alloc_single_blank_route(&wrap->route,
		map->rooms->count, map->bitfield_len) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	wrap->candidate = candidate;
	wrap->map = map;
	return (EXIT_SUCCESS);
}

static ssize_t	clean_dfs_wrap(t_dfs_wrap *wrap)
{
	size_t	i;

	i = 0;
	if (wrap->route == NULL)
	{
		if (alloc_single_blank_route(&wrap->route, wrap->map->rooms->count,
		wrap->map->bitfield_len) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		while (i < wrap->route->len)
		{
			wrap->route->route[i] = NULL;
			i++;
		}
		wrap->route->used = 0;
	}
	return (EXIT_SUCCESS);
}

void			delete_dfs_wrap(t_dfs_wrap *wrap)
{
	if (wrap->route != NULL)
	{
		if (wrap->route->route != NULL)
		{
			free(wrap->route->route);
			wrap->route->route = NULL;
		}
		if (wrap->route->bitroute != NULL)
		{
			free(wrap->route->bitroute);
			wrap->route->bitroute = NULL;
		}
		free(wrap->route);
		wrap->route = NULL;
	}
	if (wrap->visited)
	{
		free(wrap->visited);
		wrap->visited = NULL;
	}
}

ssize_t			find_routes_df(t_best *candidate, const t_map *map)
{
	t_dfs_wrap	wrap;
	t_room		*next;

	if (setup_best(candidate, map) == EXIT_FAILURE ||
		setup_dfs_wrap(&wrap, candidate, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	next = select_next_room(map->start, &wrap);
	while (next != NULL)
	{
		if (exec_find_routes_df(next, &wrap) == EXIT_FAILURE ||
			clean_dfs_wrap(&wrap) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		next = select_next_room(map->start, &wrap);
	}
	delete_dfs_wrap(&wrap);
	return (candidate->used == 0 ?
				handle_err_route_finder(2, NULL) : EXIT_SUCCESS);
}

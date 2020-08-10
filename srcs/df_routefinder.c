/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   df_routefinder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 15:49:14 by kim           #+#    #+#                 */
/*   Updated: 2020/08/07 16:32:15 by kim           ########   odam.nl         */
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

ssize_t			find_routes_df(t_best *state, t_map *map)
{
	t_find_routes_df_wrap	wrap;
	t_shortest_dist			shortwrap;

	wrap.candidate_best = state;
	if (setup_best(wrap.candidate_best, map) == EXIT_FAILURE ||
		bite_alloc(&wrap.visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	shortwrap.nb_visited = NULL;
	shortwrap.start = map->start;
	if (find_shortest_dist_option(&wrap.shortest_dist_to_end, map->start,
		NULL, &shortwrap) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (wrap.shortest_dist_to_end != NULL)
	{
		if (init_find_route_df(&wrap, wrap.shortest_dist_to_end, map) ==
			EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (find_shortest_dist_option(&wrap.shortest_dist_to_end, map->start,
			wrap.visited, &shortwrap) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	//PLACEHOLDER: free all the things
	if (shortwrap.nb_visited)
		free(shortwrap.nb_visited);
	return (EXIT_SUCCESS);
}

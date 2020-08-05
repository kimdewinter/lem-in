/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/02 19:20:25 by kim           #+#    #+#                 */
/*   Updated: 2020/08/05 15:29:32 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

inline static void	alloc_single_blank_route(t_route **dst,
												const size_t route_len,
												const size_t bitroute_len)
{
	size_t	i;

	*dst = (t_route *)malloc(sizeof(t_route) * 1);
	if (*dst != NULL)
	{
		(*dst)->len = route_len;
		(*dst)->used = 0;
		(*dst)->ants = 0;
		(*dst)->bitroute =
			(BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * bitroute_len);
		(*dst)->route = (t_room **)malloc(sizeof(t_room *) * route_len);
		if ((*dst)->bitroute != NULL && (*dst)->route != NULL)
		{
			i = 0;
			while (i < route_len)
			{
				if (i < bitroute_len)
					(*dst)->bitroute[i] = (BITFIELD_TYPE)0;
				(*dst)->route[i] = NULL;
				i++;
			}
		}
		else
		{
			if ((*dst)->bitroute != NULL)
				free((*dst)->bitroute);
			if ((*dst)->route != NULL)
				free((*dst)->route);
			free(*dst);
			*dst = NULL;
		}
	}
}

ssize_t				alloc_multiple_blank_routes(t_route ***dst,
												const size_t route_num,
												const size_t route_len,
												const size_t bitroute_len)
{
	size_t	i;

	*dst = (t_route **)malloc(sizeof(t_route *) * route_num);
	if (*dst == NULL)
		return (handle_err_route_finder(1, "alloc_multiple_blank_routes\n"));
	i = 0;
	while (i < route_num)
	{
		alloc_single_blank_route(dst[i], route_len, bitroute_len);
		if (dst[i] == NULL)
			return (handle_err_route_finder(1,
				"alloc_multiple_blank_routes\n"));
		i++;
	}
	return (EXIT_SUCCESS);
}

size_t				find_shortest_dist_to_end(t_find_routes_df_wrap *wrap,
												const t_map *map)
{
	size_t	i;

	wrap->shortest_dist_to_end = NULL;
	i = 0;
	while (i < map->start->neighbours_len)
	{
		if (wrap->shortest_dist_to_end == NULL ||
			map->start->neighbours[i]->dist_to_end <
			wrap->shortest_dist_to_end->dist_to_end)
		{
			if (room_in_bitfield(map->start->neighbours[i], wrap->visited) == 0)
				wrap->shortest_dist_to_end = map->start->neighbours[i];
		}
	}
	if (wrap->shortest_dist_to_end == NULL)
		return (0);
	else
		return (1);
}
/*
** return of 0 means no valid shortest-dist-to-end start nb was found
*/

ssize_t				setup_best(t_best *best, const t_map *map)
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

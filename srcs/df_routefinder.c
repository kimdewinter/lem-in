/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   df_routefinder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 15:49:14 by kim           #+#    #+#                 */
/*   Updated: 2020/08/05 15:31:03 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

inline static void	branch_route(t_route **dst,
									const t_route *src,
									const size_t route_len,
									const size_t bitroute_len)
{
	size_t	i;

	*dst = (t_route *)malloc(sizeof(t_route) * 1);
	if (*dst != NULL)
	{
		(*dst)->used = 0;
		(*dst)->ants = 0;
		(*dst)->len = route_len;
		(*dst)->bitroute =
			(BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * bitroute_len);
		(*dst)->route = (t_room **)malloc(sizeof(t_room *) * (*dst)->len);
		if ((*dst)->bitroute != NULL && (*dst)->route != NULL)
		{
			i = 0;
			while (i < route_len)
			{
				if (i < bitroute_len)
					(*dst)->bitroute[i] = src->bitroute[i];
				(*dst)->route[i] = (i < src->len) ? src->route[i] : NULL;
				i++;
			}
		}
		else
			handle_err_branch_or_new(dst);
	}
}

inline static void	new_route_start_nb(t_route **dst,
										const t_room *room,
										const size_t route_len,
										const size_t bitroute_len)
{
	size_t	i;

	*dst = (t_route *)malloc(sizeof(t_route) * 1);
	if (*dst != NULL)
	{
		(*dst)->ants = 0;
		(*dst)->len = route_len;
		(*dst)->bitroute =
			(BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * bitroute_len);
		(*dst)->route = (t_room **)malloc(sizeof(t_room *) * (*dst)->len);
		if ((*dst)->bitroute != NULL && (*dst)->route != NULL)
		{
			i = 0;
			while (i < route_len)
			{
				if (i < bitroute_len)
					(*dst)->bitroute[i] = (BITFIELD_TYPE)0;
				(*dst)->route[i] = (i == 0) ? room : NULL;
				i++;
			}
			(*dst)->used = 1;
		}
		else
			handle_err_branch_or_new(dst);
	}
}

static ssize_t	cont_find_route_df(t_find_routes_df_wrap *wrap,
									const t_route *parent,
									const t_map *map)
{
	t_route	*new;




	// branch_route(&new, parent, map->rooms->count, map->bitfield_len);//use this call to branch
}

static ssize_t	init_find_route_df(const t_room *begin,
									t_find_routes_df_wrap *wrap,
									const t_map *map)
{

}

ssize_t			find_routes_df(t_map *map)
{
	t_find_routes_df_wrap	wrap;

	if (map->solution.combi == NULL)
		if (setup_best(&map->solution, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (setup_best(&wrap.candidate_best, map) == EXIT_FAILURE ||
		bite_alloc(wrap.visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (find_shortest_dist_to_end(&wrap, map) == 1)
	{
		bite_add_room_to_bitfield(wrap.visited, wrap.shortest_dist_to_end, map);//to make sure a start nb that has no valid route to end is not repeatedly visited
		if (init_find_route_df(wrap.shortest_dist_to_end, &wrap, map) ==
			EXIT_FAILURE);
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
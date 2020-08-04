/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   df_routefinder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 15:49:14 by kim           #+#    #+#                 */
/*   Updated: 2020/08/04 18:19:56 by kim           ########   odam.nl         */
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
		(*dst)->len = route_len;
		(*dst)->used = 0;
		(*dst)->ants = 0;
		(*dst)->bitroute =
			(BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * bitroute_len);
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
			handle_err_allocopy_single_route(dst);
	}
}

static ssize_t	exec_find_routes_df(const t_route *parent,
									const t_map *map)
{
	t_route	*new;

	branch_route(&new, parent, map->rooms->count, map->bitfield_len);//use this call to branch
}

ssize_t			find_routes_df(t_room *room_to_begin_from,
								t_map *map)
{
	BITFIELD_TYPE	*visited;

	if (setup_best(map) == EXIT_FAILURE ||
		bite_alloc(&visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	(void)room_to_begin_from;
	return (EXIT_SUCCESS);
}
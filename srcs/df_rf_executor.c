/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   df_rf_executor.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 15:49:14 by kim           #+#    #+#                 */
/*   Updated: 2020/08/06 17:36:39 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	branch_route(t_route **dst,
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

static ssize_t	new_route_start_nb(t_route **dst,
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

static ssize_t	attach_room(t_route *route,
							const t_room *room,
							const t_map *map)
{
	route->route[route->used] = room;
	if (bite_add_room_to_bitfield(route->bitroute, room->bitroom, map) ==
		EXIT_FAILURE)
		return (EXIT_FAILURE);
}//TO DO: cannot yet expand route if needed, currently route_len is total number of rooms

static ssize_t	cont_find_route_df(t_find_routes_df_wrap *wrap,
									const t_route *parent,
									const t_room *begin,
									const t_map *map)
{
	t_route			*new;
	t_shortest_dist	shortwrap;
	t_room			*shortest;
	ssize_t			retval;

	if (branch_route(&new, parent, map->rooms->count, map->bitfield_len) ==
		EXIT_FAILURE)//copy parent route
		return (EXIT_FAILURE);
	if (attach_room(new, begin, map) == EXIT_FAILURE)//attach begin room to it
		return (EXIT_FAILURE);
	shortwrap.nb_visited = NULL;
	if (find_shortest_dist_option(&shortest, new->route[new->used],
		new->bitroute, &shortwrap) == EXIT_FAILURE)//find quickest way to end
		return (EXIT_FAILURE);
	while (shortest != NULL)
	{
		if (shortwrap.options_left == 1)//only one way to go
			attach_room(new, shortest, map);
		else//gotta branch off
		{
			retval = cont_find_route_df(wrap, new, shortest, map);
			if (retval == EXIT_FAILURE)
				return (handle_err_find_shortest_dist_option(&shortwrap));
			else if (retval == EXIT_ROUTEFOUND)
				break;
		}
		if (find_shortest_dist_option(&shortest, new->route[new->used],
			new->bitroute, &shortwrap) == EXIT_FAILURE)//find next quickest way to end
			return (EXIT_FAILURE);
	}
	//PLACEHOLDER: free all the things
}

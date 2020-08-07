/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   df_rf_executor.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 15:49:14 by kim           #+#    #+#                 */
/*   Updated: 2020/08/07 13:33:40 by kim           ########   odam.nl         */
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
	return (EXIT_SUCCESS);
}

static ssize_t	attach_room(t_route *route,
							t_room *room,
							const t_map *map)
{
	if (route->used == route->len)
		return (handle_err_route_finder(0, "attach_room, out of room_len\n"));
	route->route[route->used] = room;
	route->used++;
	if (bite_add_room_to_bitfield(route->bitroute, room->bitroom, map) ==
		EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}//TO DO: cannot yet expand route if needed, currently route_len is total number of rooms

static ssize_t	commit_route(t_find_routes_df_wrap *wrap,
								t_route *new,
								t_shortest_dist *shortwrap,
								const t_map *map)
{
	if (shortwrap->nb_visited != NULL)
	{
		free(shortwrap->nb_visited);
		shortwrap->nb_visited = NULL;
	}
	if (wrap->candidate_best.used == wrap->candidate_best.len)
		return (handle_err_route_finder(0, "commit_route\n"));
	wrap->candidate_best.combi[wrap->candidate_best.used] = new;
	wrap->candidate_best.used++;
	if (bite_add_room_to_bitfield(wrap->visited, new->bitroute, map) ==
		EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_ROUTEFOUND);//and there was much rejoicing!
}

ssize_t				find_shortest_dist_option(t_room **ret_ptr,
												const t_room *root,
												BITFIELD_TYPE *visited,
												t_shortest_dist *shortwrap)
{
	size_t	i;

	//PLACEHOLDER: something efficient for when there's only 1 way to go(room has 2 neighbours), account for dead end(1 neighbour)
	if (shortwrap->nb_visited == NULL)
	{
		shortwrap->nbs = root->neighbours;
		shortwrap->nbs_len = root->neighbours_len;
		shortwrap->nb_visited = (size_t *)malloc(sizeof(size_t) *
			shortwrap->nbs_len);
		if (shortwrap->nb_visited == NULL)
			return (handle_err_route_finder(1, "find_shortest_dist_option\n"));
		i = 0;
		while (i < shortwrap->nbs_len)
		{
			shortwrap->nb_visited[i] = 0;
			i++;
		}
	}
	i = 0;
	*ret_ptr = NULL;
	shortwrap->options_left = 0;
	while (i < shortwrap->nbs_len)
	{
		if (shortwrap->nbs[i] == NULL ||
			room_in_bitfield(shortwrap->nbs[i], visited) == 1)
			shortwrap->nb_visited[i] = 1;
		else if (shortwrap->nb_visited[i] == 0)//means room is valid options to visit
		{
			if (*ret_ptr == NULL ||
				shortwrap->nbs[i]->dist_to_end < (*ret_ptr)->dist_to_end)
				*ret_ptr = shortwrap->nbs[i];
			shortwrap->options_left++;
		}
		i++;
	}
	if (shortwrap->options_left == 1)
	{
		free(shortwrap->nb_visited);
		shortwrap->nb_visited = NULL;
	}
	return (EXIT_SUCCESS);
}

static ssize_t	cont_find_route_df(t_find_routes_df_wrap *wrap,
									const t_route *parent,
									t_room *begin,
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
		if (shortest == map->end)
		{
			attach_room(new, shortest, map);
			return (commit_route(wrap, new, &shortwrap, map));
		}
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
	if (shortwrap.nb_visited)
		free(shortwrap.nb_visited);
	if (new->bitroute)
		free(new->bitroute);
	if (new->route)
		free(new->route);
	free(new);
	return (EXIT_SUCCESS);
}

ssize_t			init_find_route_df(t_find_routes_df_wrap *wrap,
									t_room *begin,
									const t_map *map)
{
	t_route	*new;
	ssize_t	retval;

	if (alloc_single_blank_route(&new, map->rooms->count, map->bitfield_len)
		== EXIT_FAILURE)
		return (EXIT_FAILURE);
	retval = cont_find_route_df(wrap, new, begin, map);
	free(new->bitroute);
	free(new->route);
	free(new);
	return (retval);
}

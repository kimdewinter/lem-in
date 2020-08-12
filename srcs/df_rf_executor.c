/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   df_rf_executor.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 15:49:14 by kim           #+#    #+#                 */
/*   Updated: 2020/08/12 15:37:11 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	branch_route(t_route **dst,
									const t_route *src,
									const size_t route_len)
{
	size_t	i;

	*dst = (t_route *)malloc(sizeof(t_route) * 1);
	if (*dst != NULL)
	{
		(*dst)->bitroute = NULL;
		(*dst)->used = src->used;
		(*dst)->ants = 0;
		(*dst)->len = route_len;
		(*dst)->route = (t_room **)malloc(sizeof(t_room *) * (*dst)->len);
		if ((*dst)->route != NULL)
		{
			i = 0;
			while (i < route_len)
			{
				(*dst)->route[i] = (i < src->len) ? src->route[i] : NULL;
				i++;
			}
			return (EXIT_SUCCESS);
		}
		else
			handle_err_branch_or_new(dst);
	}
	return (EXIT_FAILURE);
}

static ssize_t	attach_room(t_route *route,
							BITFIELD_TYPE *visited,
							t_room *room)
{
	if (route->used == route->len)
		return (handle_err_route_finder(0, "attach_room, out of room_len\n"));
	route->route[route->used] = room;
	route->used++;
	bite_add_room_to_bitfield(room, visited);
	return (EXIT_SUCCESS);
}//TO DO: cannot yet expand route if needed, currently route_len is total number of rooms

static ssize_t	commit_route(t_find_routes_df_wrap *wrap,
								t_route *new,
								t_shortest_dist *shortwrap,
								const t_map *map)
{
	size_t	i;

	if (bite_alloc(&new->bitroute, map) == EXIT_FAILURE)
		return (handle_err_route_finder(1, "commit_route\n"));
	i = 0;
	while (i < new->used)
	{
		bite_add_room_to_bitfield(new->route[i], new->bitroute);
		i++;
	}
	if (shortwrap->nb_visited != NULL)
	{
		free(shortwrap->nb_visited);
		shortwrap->nb_visited = NULL;
	}
	if (wrap->candidate_best->used == wrap->candidate_best->len)
		return (handle_err_route_finder(0, "commit_route\n"));
	wrap->candidate_best->combi[wrap->candidate_best->used] = new;
	wrap->candidate_best->used++;
	return (EXIT_ROUTEFOUND);//and there was much rejoicing!
}

static void			clean_shortwrap(t_shortest_dist *shortwrap)
{
	shortwrap->nbs = NULL;
	shortwrap->nbs_len = 0;
	if (shortwrap->nb_visited != NULL)
	{
		free(shortwrap->nb_visited);
		shortwrap->nb_visited = NULL;
	}
	shortwrap->options_left = 0;
	shortwrap->nb_vis_i_of_ret = -1;
}

ssize_t				find_shortest_dist_option(t_room **ret_ptr,
												t_room *root,
												BITFIELD_TYPE *visited,
												t_shortest_dist *shortwrap)
{
	size_t	i;

	//PLACEHOLDER: something efficient for when there's only 1 way to go(room has 2 neighbours), account for dead end(1 neighbour)
	if (shortwrap->nb_visited == NULL)
	{
		shortwrap->nbs = root->neighbours;
		shortwrap->nbs_len = root->neighbours_len;
		shortwrap->nb_visited = (ssize_t *)malloc(sizeof(ssize_t) *
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
	shortwrap->nb_vis_i_of_ret = -1;
	while (i < shortwrap->nbs_len)
	{
		if (shortwrap->nbs[i] == NULL || shortwrap->nbs[i] ==
			shortwrap->start || (visited != NULL && room_in_bitfield(
			shortwrap->nbs[i], visited) == 1))
			shortwrap->nb_visited[i] = 1;
		else if (shortwrap->nb_visited[i] == 0)//means room is valid options to visit
		{
			if (*ret_ptr == NULL ||
				shortwrap->nbs[i]->dist_to_end < (*ret_ptr)->dist_to_end)
			{
				*ret_ptr = shortwrap->nbs[i];
				shortwrap->nb_vis_i_of_ret = i;
			}
			shortwrap->options_left++;
		}
		i++;
	}
	if (*ret_ptr != NULL)
		shortwrap->nb_visited[shortwrap->nb_vis_i_of_ret] = 1;
	else
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

	if (branch_route(&new, parent, map->rooms->count) == EXIT_FAILURE)//copy parent route
		return (EXIT_FAILURE);
	if (attach_room(new, wrap->visited, begin) == EXIT_FAILURE)//attach begin room to it
		return (EXIT_FAILURE);
	shortwrap.nb_visited = NULL;
	shortwrap.start = map->start;
	if (find_shortest_dist_option(&shortest, new->route[new->used - 1],
		wrap->visited, &shortwrap) == EXIT_FAILURE)//find quickest way to end
		return (EXIT_FAILURE);
	while (shortest != NULL)
	{
		if (shortest == map->end)
		{
			attach_room(new, wrap->visited, shortest);
			return (commit_route(wrap, new, &shortwrap, map));
		}
		if (shortwrap.options_left == 1)//only one way to go
		{
			attach_room(new, wrap->visited, shortest);
			clean_shortwrap(&shortwrap);
		}
		else//gotta branch off
		{
			retval = cont_find_route_df(wrap, new, shortest, map);
			if (retval == EXIT_FAILURE)
				return (handle_err_find_shortest_dist_option(&shortwrap));
			else if (retval == EXIT_ROUTEFOUND)
				break;
		}
		if (find_shortest_dist_option(&shortest, new->route[new->used - 1],
			wrap->visited, &shortwrap) == EXIT_FAILURE)//find next quickest way to end
			return (EXIT_FAILURE);
	}
	if (shortwrap.nb_visited != NULL)
		free(shortwrap.nb_visited);
	if (new->bitroute != NULL)
		free(new->bitroute);
	if (new->route != NULL)
		free(new->route);
	free(new);
	return (shortest == NULL ? EXIT_SUCCESS : EXIT_ROUTEFOUND);
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

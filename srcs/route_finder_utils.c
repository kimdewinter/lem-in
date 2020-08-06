/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/02 19:20:25 by kim           #+#    #+#                 */
/*   Updated: 2020/08/06 17:24:30 by kim           ########   odam.nl         */
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

ssize_t				find_shortest_dist_option(t_room **ret_ptr,
												const t_room *root,
												BITFIELD_TYPE *visited,
												t_shortest_dist *shortwrap)
{
	ssize_t	i;

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
	while (i < shortwrap->nbs_len)
	{
		if (shortwrap->nbs[i] == NULL ||
			room_in_bitfield(shortwrap->nbs[i], visited) == 1)
			shortwrap->nb_visited = 1;
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

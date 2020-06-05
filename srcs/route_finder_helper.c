/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder_helper.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 16:21:39 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/04 16:23:30 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int			has_path_to_conj(t_room *curr, t_room *conj)
{
	if (curr->spe == 1)
		return (1);
	if ((curr->bitconj[conj->room_i / BITFIELD_SIZE] &
	((BITFIELD_TYPE)1 << (63 - conj->room_i % BITFIELD_SIZE))) != 0)
		return (1);
	return (0);
}

int			is_new_conj(t_room *src, t_room *curr, t_subpath *spt)
{
	size_t	i;
	size_t	viable_nbs;

	viable_nbs = 0;
	i = 0;
	while (i < curr->neighbours_len)
	{
		if (!(curr->neighbours[i] == src
		|| has_path_to_conj(curr->neighbours[i], spt->conj) == 1
		|| src->spe == 1))
			viable_nbs++;
		if (viable_nbs > 1)
			return (1);
		i++;
	}
	return (0);
}

static size_t			increase_routes_size(t_room **dst)
{
	size_t		i;
	size_t		new_size;
	t_subpath	**new_routes;

	i = 0;
	new_size = (*dst)->routes_size + 1;
	new_routes = (t_subpath **)malloc(sizeof(t_subpath *) * new_size);
	if (new_routes)
	{
		while (i < (*dst)->routes_size)
		{
			new_routes[i] = (*dst)->routes[i];
			i++;
		}
		if ((*dst)->routes)
			free ((*dst)->routes);
		(*dst)->routes = new_routes;
		(*dst)->routes_size = new_size;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

size_t			add_subpath(t_room *dst, t_subpath *pt)
{
	if (dst->num_options < dst->routes_size)
	{
		dst->routes[dst->num_options] = pt;
		dst->num_options++;
		return (EXIT_SUCCESS);
	}
	else
	{
		if (increase_routes_size(&dst) == EXIT_SUCCESS)
		{
			dst->routes[dst->num_options] = pt;
			dst->num_options++;
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
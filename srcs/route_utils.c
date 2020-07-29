/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:34:22 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/28 14:57:29 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t		add_to_path(t_subpath *pt, t_room *add, t_map *map)
{
	if (pt->start_ind < 0)
	{
		if (increase_route_size(&pt, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	pt->path[pt->start_ind] = add;
	pt->start_ind -= 1;
	pt->len += 1;
	pt->segment_len += 1;
	return (EXIT_SUCCESS);
}

ssize_t				add_path_to_room(t_room *dst, t_map *map,
t_subpath **new)
{
	if (dst->num_options >= dst->routes_size)
	{
		if (increase_routes_size(&dst, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	dst->routes[dst->num_options] = *new;
	dst->num_options++;
	if ((*new)->conj != map->end)
		add_to_bitfield((*new)->conj, dst->bitconj);
	return (EXIT_SUCCESS);
}

t_room			**new_path(size_t size)
{
	t_room	**new;

	new = (t_room **)malloc(sizeof(t_room *) * size);
	return (new);
}

ssize_t		new_subpath(t_subpath **new, t_room *conj, t_map *map)
{
	*new = (t_subpath *)malloc(sizeof(t_subpath));
	if (*new)
	{
		(*new)->sp = 0;
		(*new)->conj = conj;
		(*new)->size = 0;
		(*new)->segment_len = 0;
		(*new)->len = 0;
		(*new)->start_ind = -1;
		(*new)->start = NULL;
		(*new)->end = NULL;
		(*new)->path = NULL;
		(*new)->next = NULL;
		if (bite_alloc(&(*new)->bitconj, map) == EXIT_FAILURE)
		{
			free (*new);
			(*new) = NULL;
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

ssize_t		create_new_path(t_subpath **new, t_subpath *pt, t_room *conj, 
t_map *map)
{
	new_subpath(new, conj, map);
	if (*new)
	{
		(*new)->len += 1;
		if (pt)
			(*new)->len += pt->len;
		(*new)->next = pt;
		(*new)->start = conj;
		if (pt != NULL)
		{
			(*new)->end = pt->end;
			if (bite_bitroute_copy((*new)->bitconj, pt->bitconj, map)
			== EXIT_FAILURE)
			{
				free (*new);
				return (EXIT_FAILURE);
			}
		}
		else
			(*new)->end = conj;	
		if (conj != map->end)
			add_to_bitfield(conj, (*new)->bitconj);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
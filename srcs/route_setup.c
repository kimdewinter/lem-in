/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_setup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 16:45:15 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/02 17:14:41 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

t_subpath		*new_subpath(t_room *conj)
{
	t_subpath	*new;

	new = (t_subpath *)malloc(sizeof(t_subpath));
	if (new)
	{
		new->conj = conj;
		new->len = 0;
		return (new);
	}
	return (NULL);
}

t_room					**new_path(size_t size)
{
	t_room	**new;

	new = (t_room **)malloc(sizeof(t_room *) * size);
	return (new);
}

static size_t		add_new_conj_subpath_end(t_room *dst,
t_room *conj)
{
	t_subpath	*new;

	new = new_subpath(conj);
	if (new != NULL)
	{
		new->path = new_path(1);
		if (new->path)
		{
			new->path[0] = NULL;
			if (add_subpath(dst, new) == EXIT_SUCCESS)
				return (EXIT_SUCCESS);
			free (new->path);
		}
		free (new);
	}
	return (EXIT_FAILURE);
}

size_t						setup_paths(t_map *map)
{
	t_room *end;

	end = map->end;
	if (add_new_conj_subpath_end(end, end) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
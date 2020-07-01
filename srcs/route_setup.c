/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_setup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 16:45:15 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/01 13:24:52 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

size_t		new_subpath(t_subpath **new, t_room *conj, t_map *map)
{
	*new = (t_subpath *)malloc(sizeof(t_subpath));
	if (*new)
	{
		(*new)->sp = 0;
		(*new)->new_conj = 1;
		(*new)->conj = conj;
		(*new)->size = 0;
		(*new)->segment_len = 0;
		(*new)->len = 0;
		(*new)->start = -1;
		(*new)->added_this_turn = 1;
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

t_room					**new_path(size_t size)
{
	t_room	**new;
	size_t	i;

	i = 0;
	new = (t_room **)malloc(sizeof(t_room *) * size);
	if (new)
	{
		while (i < size)
		{
			new[i] = NULL;
			i++;
		}
		return (new);
	}
	return (NULL);
}

static size_t		add_new_conj_subpath_end(t_room *src, t_room *dst,
t_room *conj, t_map *map)
{
	t_subpath	*new;

	(void)dst;
	if (new_subpath(&new, conj, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (new)
	{
		printf("SRC IN END %s\n", src->name);
		if (add_path(NULL, NULL, new, map) == EXIT_SUCCESS)
		{
			new->len = 0;
			print_path(map->end->routes[0]);
			exit (0);
			return (EXIT_SUCCESS);
		}
		free (new);
	}
	return (EXIT_FAILURE);
}

size_t						setup_paths(t_map *map)
{
	t_room *end;

	end = map->end;
	if (add_new_conj_subpath_end(end, end, end, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	printf("After setup paths\n");
	return (EXIT_SUCCESS);
}
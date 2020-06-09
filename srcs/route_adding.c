/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_adding.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:34:22 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/09 12:24:09 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static void				add_bite_conj(t_room *dst, t_room *conj)
{
	dst->bitconj[conj->room_i / BITFIELD_SIZE] |=
	(BITFIELD_TYPE)1 << (63 - conj->room_i % BITFIELD_SIZE);
}

size_t		add_new_conj_subpath(t_room *dst, t_room *src)
{
	t_subpath	*new;

	add_bite_conj(dst, src);
	new = new_subpath(src);
	if (new)
	{
		new->path = new_path(1);
		new->len = 1;
		if (new->path)
		{
			new->path[0] = src;
			if (add_subpath(dst, new) == EXIT_SUCCESS)
					return (EXIT_SUCCESS);
		}
		free (new);
	}
	return (EXIT_FAILURE);
}

static t_subpath	*copy_subpath(t_subpath *pt)
{
	t_subpath	*new;
	size_t		i;

	i = 0;
	new = new_subpath(pt->conj);
	if (new)
	{
		new->len = pt->len + 1;
		new->path = new_path(new->len);
		if (new->path)
		{
			while (i < pt->len)
			{
				new->path[i + 1] = pt->path[i];
				i++;
			}
			return (new);
		}
		free (new);
	}
	return (NULL);
}

size_t			add_to_conj_path(t_room *dst, t_room *src,
t_subpath *pt)
{
	t_subpath	*new;

	add_bite_conj(dst, pt->conj);
	new = copy_subpath(pt);
	if (new)
	{
		new->path[0] = src;
		{
			if (add_subpath(dst, new) == EXIT_SUCCESS)
				return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
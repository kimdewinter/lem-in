/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_weights_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 13:09:39 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/25 13:12:41 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static t_weight	*new_weight_item(size_t round, t_room *dst)
{
	t_weight	*new;

	new = (t_weight *)malloc(sizeof(t_weight));
	if (new)
	{
		new->dst = dst;
		new->next = NULL;
		new->dist = round;
		return (new);
	}
	return (NULL);
}

static void		add_to_q(t_weight **q, t_weight *new)
{
	t_weight	*tmp;

	tmp = *q;
	if (tmp == NULL)
		*q = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void			remove_q_item(t_weight **q)
{
	t_weight	*tmp;
	t_weight	*prev;

	tmp = *q;
	if (tmp != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
		free(prev);
		*q = tmp;
	}
}

ssize_t			add_q_item(t_weight **q, size_t round, t_room *dst)
{
	t_weight	*new;

	new = new_weight_item(round, dst);
	if (new)
	{
		add_to_q(q, new);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

ssize_t			create_q(t_weight_wrap **qr, BITFIELD_TYPE *in_paths,
t_map *map)
{
	*qr = (t_weight_wrap *)malloc(sizeof(t_weight_wrap));
	if (*qr)
	{
		(*qr)->q = (t_weight **)malloc(sizeof(t_weight *));
		if ((*qr)->q)
		{
			*(*qr)->q = NULL;
			if (bite_alloc(&(*qr)->visited, map) == EXIT_SUCCESS)
			{
				(*qr)->in_paths = in_paths;
				return (EXIT_SUCCESS);
			}
			free((*qr)->q);
		}
		free(*qr);
		*qr = NULL;
	}
	return (EXIT_FAILURE);
}

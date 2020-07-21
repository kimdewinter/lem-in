/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_weights.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/21 09:24:09 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/21 09:24:09 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static t_weight	*new_weight_item(size_t	round, t_room *dst)
{
	t_weight	*new;

	new = (t_weight *)malloc(sizeof(t_weight));
	if (new)
	{
		new->dst = dst;
		new->next = NULL;
		new->weight = round;
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

static void		remove_q_item(t_weight **q)
{
	t_weight	*tmp;
	t_weight	*prev;

	tmp = *q;
	if (tmp != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
		free (prev);
		*q = tmp;
	}
}

static ssize_t	add_q_item(t_weight **q, size_t round, t_room *dst)
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

static ssize_t	add_start_nbs(t_room *start, t_weight **q,
BITFIELD_TYPE *visited, size_t weight)
{
	size_t	i;

	i = 0;
	add_to_bitfield(start, visited);
	while (i < start->neighbours_len)
	{
		if (add_q_item(q, weight, start->neighbours[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		add_to_bitfield(start->neighbours[i], visited);
		i++;
	}
	return (EXIT_SUCCESS);
}

static ssize_t	create_q(t_weight ***q)
{
	*q = (t_weight **)malloc(sizeof(t_weight *));
	 if (!(*q))
	 	return (EXIT_FAILURE);
	*(*q)= NULL;
	return (EXIT_SUCCESS);
}

static ssize_t	add_nbs_to_q(t_weight **q, BITFIELD_TYPE *visited)
{
	size_t	i;

	i = 0;
	while (i < (*q)->dst->neighbours_len)
	{
		if (room_in_bitfield((*q)->dst->neighbours[i], visited) == 0)
		{
			if (add_q_item(q, (*q)->weight + 1, (*q)->dst->neighbours[i])
			== EXIT_FAILURE)
				return (EXIT_FAILURE);
			add_to_bitfield((*q)->dst->neighbours[i], visited);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

ssize_t		set_weights(t_map *map)
{
	t_weight		**q;
	BITFIELD_TYPE	*visited;
	size_t			weight;

	weight = 1;
	if (create_q(&q) == EXIT_FAILURE ||
	bite_alloc(&visited, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	add_start_nbs(map->start, q, visited, weight);
	while (*q)
	{
		(*q)->dst->start_dst = (*q)->weight;
		if (add_nbs_to_q(q, visited) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		remove_q_item(q);
	}
	// debug(map);
	// exit (0);
	return (EXIT_SUCCESS);
}
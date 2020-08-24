/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_weights.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 16:10:30 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/23 20:07:53 by lravier       ########   odam.nl         */
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

static ssize_t	add_start_nbs_to_q(t_room *start, t_weight_wrap *qr, size_t weight)
{
	size_t	i;

	i = 0;
	bite_add_room_to_bitfield(start, qr->visited);
	while (i < start->neighbours_len)
	{
		if (qr->in_paths == NULL
		|| room_in_bitfield(start->neighbours[i], qr->in_paths) == 0)
		{
			if (add_q_item(qr->q, weight, start->neighbours[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		bite_add_room_to_bitfield(start->neighbours[i], qr->visited);
		i++;
	}
	return (EXIT_SUCCESS);
}

static ssize_t	create_q(t_weight_wrap **qr, BITFIELD_TYPE *in_paths, t_map *map)
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
			free ((*qr)->q);
		}
		free (*qr);
		*qr = NULL;
	}
	return (EXIT_FAILURE);
}

static ssize_t	add_nbs_to_q(t_weight **q, BITFIELD_TYPE *visited)
{
	size_t	i;

	i = 0;
	while (i < (*q)->dst->neighbours_len)
	{
		if (room_in_bitfield((*q)->dst->neighbours[i], visited) == 0)
		{
			if (add_q_item(q, (*q)->dist + 1, (*q)->dst->neighbours[i])
			== EXIT_FAILURE)
				return (EXIT_FAILURE);
			bite_add_room_to_bitfield((*q)->dst->neighbours[i], visited);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

ssize_t		set_weights(t_map *map, int flow, BITFIELD_TYPE *in_paths)
{
	t_weight_wrap		*qr;
	size_t				weight;

	weight = 1;
	if (create_q(&qr, in_paths, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (flow == 1)
	{
		map->start->dist_to_start = 0;
		add_start_nbs_to_q(map->start, qr, weight);
	}
	if (flow == -1)
	{
		map->end->dist_to_end = 0;
		add_start_nbs_to_q(map->end, qr, weight);
	}
	while (*(qr->q))
	{
		if (flow == 1)
			(*(qr->q))->dst->dist_to_start = (*(qr->q))->dist;
		else
			(*(qr->q))->dst->dist_to_end = (*(qr->q))->dist;
		if ((flow == 1 && (*(qr->q))->dst != map->end)
		|| (flow == -1 && (*(qr->q))->dst != map->start))
		{
			if (qr->in_paths == NULL
			|| room_in_bitfield((*(qr->q))->dst, qr->in_paths) == 0)
			{
				if (add_nbs_to_q(qr->q, qr->visited) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
		}
		remove_q_item(qr->q);
	}
	free (qr->q);
	free (qr->visited);
	free (qr);
	return (EXIT_SUCCESS);
}

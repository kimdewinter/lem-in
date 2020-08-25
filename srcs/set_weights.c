/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_weights.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 16:10:30 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/25 13:33:23 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t		add_start_nbs_to_q(t_room *start, t_weight_wrap *qr,
size_t weight)
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

static ssize_t		add_nbs_to_q(t_weight **q, BITFIELD_TYPE *visited)
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

static void			free_weight_q(t_weight_wrap **qr)
{
	while (*(*qr)->q)
		remove_q_item((*qr)->q);
	free((*qr)->visited);
	(*qr)->visited = NULL;
	free((*qr)->q);
	(*qr)->q = NULL;
	free(*qr);
	*qr = NULL;
}

static ssize_t		execute_q_weight_item(int flow, t_weight_wrap *qr,
t_map *map)
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
			{
				free_weight_q(&qr);
				return (EXIT_FAILURE);
			}
		}
	}
	remove_q_item(qr->q);
	return (EXIT_SUCCESS);
}

ssize_t				set_weights(t_map *map, int flow, BITFIELD_TYPE *in_paths)
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
		if (execute_q_weight_item(flow, qr, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	free_weight_q(&qr);
	return (EXIT_SUCCESS);
}

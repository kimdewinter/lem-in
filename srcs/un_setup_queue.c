/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_setup_queue.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 13:20:05 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/13 19:50:47 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int		solve_queue_conflict_start(t_conn_wrap *qr, t_connection *tmp,
t_map *map, size_t *i)
{
	t_connection	*iter;

	iter = *(qr->q);
	while (iter)
	{
		if (iter->dst == tmp->dst)
		{
			if (iter->dist > tmp->dist)
			{
				remove_path(iter, map);
				remove_q_item_un(qr, iter);
				tmp->add = 1;
				return (1);
			}
			else
			{
				*i -= remove_path(tmp, map);
				tmp->add = 0;
				return (1);
			}
		}
		iter = iter->next;
	}
	return (0);
}

ssize_t			un_add_start_nbs_to_q(t_room *start, t_conn_wrap *qr,
t_map *map, int *changed)
{
	size_t			i;
	t_connection	tmp;
	BITFIELD_TYPE	*atq;

	i = 0;
	setup_conn(&tmp, start);
	add_to_bitfield(start, qr->visited);
	if (bite_alloc(&atq, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (i < start->neighbours_len)
	{
		setup_conn(&tmp, start);
		set_conn(&tmp, start->neighbours[i]);
		if (check_conn(&tmp, &i, changed, map) == 1)
		{
			if (room_in_bitfield(tmp.dst, atq) == 1 && tmp.dst != map->end)
				*changed += solve_queue_conflict_start(qr, &tmp, map, &i);
			if (add_q_item_un(qr, &tmp, NULL, atq) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	free(atq);
	return (EXIT_SUCCESS);
}

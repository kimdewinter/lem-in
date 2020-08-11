/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_setup_queue.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 13:45:28 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/05 13:45:28 by lravier       ########   odam.nl         */
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
				del_tube(iter->dst, iter->dst_nb, map);
				del_tube(iter->dst_nb, iter->dst, map);
				del_tube(iter->src, iter->src_nb, map);
				del_tube(iter->src_nb, iter->src, map);
				remove_q_item_un(qr, iter);
				tmp->add = 1;
				return (1);
			}
			else
			{
				*i -= del_tube(tmp->src, tmp->src_nb, map);
				del_tube(tmp->src_nb, tmp->src, map);
				del_tube(tmp->dst, tmp->dst_nb, map);
				del_tube(tmp->dst_nb, tmp->dst, map);
				tmp->add = 0;
				return (1);
			}
		}
		iter = iter->next;
	}
	return (0);
}

ssize_t			un_add_start_nbs_to_q(t_room *start, t_conn_wrap *qr, t_map *map,
int	*changed)
{
	size_t			i;
	t_connection	tmp;
	BITFIELD_TYPE	*added_to_queue;

	i = 0;
	setup_conn(&tmp, start);
	add_to_bitfield(start, qr->visited);
	if (bite_alloc(&added_to_queue, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (i < start->neighbours_len)
	{
		setup_conn(&tmp, start);
		if (start->neighbours[i] != NULL)
		{
			tmp.add = 1;
			set_conn(&tmp, start->neighbours[i]);
			if (start->neighbours[i]->is_junction == 0)
				find_real_nb(&tmp, map);
			if (tmp.dst == start)
			{
				if (DEBUG == 1)
				{
					printf("Loop\n");
					print_connection(&tmp);
				}
				*changed = 1;
				del_tube(start->neighbours[i], start, map);
				i -= del_tube(start, start->neighbours[i], map);
				del_tube(start, tmp.dst_nb, map);
				del_tube(tmp.dst_nb, start, map);
				// exit (0);
			}
			else if (tmp.dst == NULL)
			{
				if (DEBUG == 1)
					printf("Nowhere to go\n");
				*changed = 1;
				i -= handle_nowhere_to_go(start, start->neighbours[i], map);
				// del_tube(start->neighbours[i], start, map);
				// i -= del_tube(start, start->neighbours[i], map);
			}
			else
			{
				if (room_in_bitfield(tmp.dst, added_to_queue) == 1
				&& tmp.dst != map->end)
				{
					if (DEBUG == 1)
						printf("Already a dst %s\n", tmp.dst->name);
					*changed += solve_queue_conflict_start(qr, &tmp, map, &i);
					if (*changed == 2)
						*changed = 1;
				}
				if (tmp.add == 1)
				{
					if (add_q_item_un(qr, &tmp) == EXIT_FAILURE)
					{
						free (added_to_queue);
						return (EXIT_FAILURE);
					}
					add_to_bitfield(tmp.dst, added_to_queue);
				}
			}
		}
		i++;
	}
	free (added_to_queue);
	return (EXIT_SUCCESS);
}
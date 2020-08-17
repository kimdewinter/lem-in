/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_update_queue.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 11:50:05 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/17 12:22:50 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t			update_queue_un(t_conn_wrap *qr, t_map *map, int *changed)
{
	size_t			len;
	size_t			i;
	t_connection	*iter;
	t_connection	*prev;

	iter = *(qr->q);
	len = qr->items;
	i = 0;
	while (i < len && iter)
	{
		if (room_in_bitfield(iter->dst, qr->visited) == 0
		&& iter->dst != map->end)
		{
			if (un_add_nbs_to_queue(iter->dst, qr, map, changed) ==
			EXIT_FAILURE)
				return (EXIT_FAILURE);
			add_to_bitfield(iter->dst, qr->visited);
		}
		prev = iter;
		iter = iter->next;
		remove_q_item_un(qr, prev);
		i++;
	}
	return (EXIT_SUCCESS);
}

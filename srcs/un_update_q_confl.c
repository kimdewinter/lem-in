/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_update_q_confl.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 12:20:00 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/17 12:24:25 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int		remove_conflict_conn(t_connection *iter, t_connection *tmp,
t_conn_wrap *qr, t_map *map)
{
	if (iter->dist > tmp->dist)
	{
		remove_path(iter, map);
		remove_q_item_un(qr, iter);
		tmp->add = 1;
		return (0);
	}
	else
	{
		remove_path(tmp, map);
		tmp->add = 0;
		return (1);
	}
}

int				solve_queue_conflict(t_conn_wrap *qr, t_connection *tmp,
t_map *map, size_t *added)
{
	size_t			i;
	t_connection	*iter;
	int				res;

	i = 0;
	iter = *(qr->q);
	while (iter->next)
		iter = iter->next;
	while (i < *added)
	{
		if (iter->dst == tmp->dst
		&& iter->src == tmp->src)
		{
			res = remove_conflict_conn(iter, tmp, qr, map);
			if (res == 0)
				*added -= 1;
			return (res);
		}
		i++;
		iter = iter->prev;
	}
	return (0);
}

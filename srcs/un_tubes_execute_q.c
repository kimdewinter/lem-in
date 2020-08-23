/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_tubes_execute_q.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 15:47:44 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/23 12:03:29 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void			execute_queue_item(t_conn_wrap *qr, t_connection **iter,
int *changed, t_map *map)
{
	t_connection *prev;

	prev = NULL;
	if (!((*iter)->src == map->start && (*iter)->dst == map->end))
	{
		if (del_un_tubes(*iter, changed, map) == 1
		&& (*iter)->dst != NULL)
			*iter = (*iter)->next;
		else
		{
			prev = *iter;
			*iter = (*iter)->next;
			remove_q_item_un(qr, prev);
		}
	}
	else
		*iter = (*iter)->next;
}

static ssize_t		reset_q(t_conn_wrap *qr, int *changed, t_map *map,
t_connection **iter)
{
	if (update_queue_un(qr, map, changed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*iter = *(qr->q);
	return (EXIT_SUCCESS);
}

ssize_t				execute_queue_un(t_conn_wrap *qr, t_map *map, int *changed)
{
	t_connection	*iter;
	t_connection	*prev;

	iter = *(qr->q);
	prev = NULL;
	while (iter)
	{
		remove_duplicate_paths(&iter, map, changed);
		if (iter->dst->is_junction == 0)
			find_real_nb(iter);
		if (check_conn(iter, NULL, changed, map) == 1)
			execute_queue_item(qr, &iter, changed, map);
		else
		{
			prev = iter;
			iter = iter->next;
			remove_q_item_un(qr, prev);
		}
		if (iter == NULL)
		{
			if (reset_q(qr, changed, map, &iter) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

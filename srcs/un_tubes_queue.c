/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_utils_unnecessary_tubes.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 16:31:00 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/04 16:31:00 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			remove_q_item_un(t_conn_wrap *qr, t_connection *item)
{
	if (item == NULL)
		return ;
	if (item->prev == NULL && item->next == NULL)
	{
		free (item);
		item = NULL;
		*(qr->q) = NULL;
	}
	else if (item->prev == NULL)
	{
		item->next->prev = NULL;
		*(qr->q) = item->next;
		free (item);
		item = NULL;
	}
	else if (item->next == NULL)
	{
		item->prev->next = NULL;
		free (item);
		item = NULL;
	}
	else
	{
		item->prev->next = item->next;
		item->next->prev = item->prev;
		free (item);
		item = NULL;
	}
	qr->items--;
}

static void		add_to_q(t_conn_wrap *qr, t_connection *new)
{
	t_connection	*tmp;

	tmp = *(qr->q);
	if (tmp == NULL)
		*(qr->q) = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	qr->items++;
}

ssize_t			add_q_item_un(t_conn_wrap *qr, t_connection *item)
{
	t_connection	*new;

	new = new_connection(item);
	if (new)
	{
		add_to_q(qr, new);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_tubes_queue.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 16:31:00 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/17 13:10:05 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_connection		*new_connection(t_connection *item)
{
	t_connection	*new;

	new = (t_connection *)malloc(sizeof(t_connection));
	if (new)
	{
		new->add = 1;
		new->src = item->src;
		new->src_nb = item->src_nb;
		new->dst = item->dst;
		new->dst_nb = item->dst_nb;
		new->dist = item->dist;
		new->prev = NULL;
		new->next = NULL;
		return (new);
	}
	return (NULL);
}

void				remove_q_item_un_other(t_connection *item)
{
	if (item->next == NULL)
	{
		item->prev->next = NULL;
		free(item);
		item = NULL;
	}
	else
	{
		item->prev->next = item->next;
		item->next->prev = item->prev;
		free(item);
		item = NULL;
	}
}

void				remove_q_item_un(t_conn_wrap *qr, t_connection *item)
{
	if (item == NULL)
		return ;
	if (item->prev == NULL && item->next == NULL)
	{
		free(item);
		item = NULL;
		*(qr->q) = NULL;
	}
	else if (item->prev == NULL)
	{
		item->next->prev = NULL;
		*(qr->q) = item->next;
		free(item);
		item = NULL;
	}
	else
		remove_q_item_un_other(item);
	qr->items--;
}

static void			add_to_q(t_conn_wrap *qr, t_connection *new)
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

ssize_t				add_q_item_un(t_conn_wrap *qr, t_connection *item,
size_t *added, BITFIELD_TYPE *added_to_queue)
{
	t_connection	*new;

	if (item->add == 1)
	{
		if (added != NULL)
			*added += 1;
		bite_add_room_to_bitfield(item->dst, added_to_queue);
		new = new_connection(item);
		if (new)
		{
			add_to_q(qr, new);
			return (EXIT_SUCCESS);
		}
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

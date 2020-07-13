/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 11:45:52 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/13 13:14:53 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_queue		*new_queue_item(t_subpath *pt, t_room *dst, t_room *src)
{
	t_queue	*new;

	new = (t_queue *)malloc(sizeof(t_queue));
	if (new)
	{
		new->handled = 0;
		new->src = src;
		new->dst = dst;
		new->path = pt;
		new->next = NULL;
		new->prev = NULL;
		return (new);
	}
	return (NULL);
}

void		add_item_queue(t_qwrap **qr, t_queue *new)
{
	t_queue	*tmp;

	tmp = (*qr)->last;
	(*qr)->items++;
	if (tmp == NULL)
	{
		(*qr)->last = new;
		*((*qr)->queue) = new;
	}
	else
	{
		(*qr)->last->next = new;
		new->prev = (*qr)->last;
		(*qr)->last = new;
	}
}

void		remove_queue_item(t_qwrap *qr, t_queue *item)
{
	if (item == NULL)
		return ;
	qr->items--;
	if (item->prev == NULL && item->next == NULL)
	{
		free (item);
		qr->last = NULL;
		*(qr->queue) = NULL;
	}
	else if (item->prev == NULL)
	{
		item->next->prev = NULL;
		*(qr->queue) = item->next;
		free (item);
	}
	else if (item->next == NULL)
	{
		item->prev->next = NULL;
		qr->last = item->prev;
		free (item);
	}
	else
	{
		item->prev->next = item->next;
		item->next->prev = item->prev;
		free (item);
	}
}

ssize_t			add_to_queue(t_qwrap *qr, t_room *src, t_room *dst,
t_subpath *pt)
{
	t_queue *new;

	new = NULL;
	new = new_queue_item(pt, dst, src);
	if (new == NULL)
		return (EXIT_FAILURE);
	add_item_queue(&qr, new);
	return (EXIT_SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_conflicts.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/21 20:04:54 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/21 20:04:54 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		solve_path_conflict(t_room *dst, t_subpath *new)
{
	size_t	i;
	size_t	found;

	i = dst->num_options;
	found = 0;
	while (i < dst->num_options)
	{
		if (dst->routes[i]->conj == new->conj)
		{
			found++;
			if (new->segment_len < dst->routes[i]->segment_len)
			{
				delete_path(&(dst->routes[i]));
				dst->routes[i] = new;
				return (0);
			}
		}
		i--;
	}
	if (found == 0)
		return (-1);
	return (1);
}

int		solve_queue_conflict(t_qwrap *qr, t_subpath *new, t_room *dst)
{
	t_queue	*iter;

	iter = qr->last;
	while (iter && iter->handled == 0)
	{
		if (iter->dst == dst && iter->src == new->conj)
		{
			if (new->segment_len < iter->path->segment_len)
			{
				remove_queue_item(qr, iter);
				return (1);
			}
		}
		iter = iter->prev;
	}
	return (0);
}
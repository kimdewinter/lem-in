/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_route_finding.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 19:51:48 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/04 20:53:39 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void		free_subpath_path(t_room **path, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free (path[i]);
		i++;
	}
}

void		free_subpath(t_subpath *pt)
{
	free_subpath_path(pt->path, pt->len);
	free (pt->bitconj);
}

void		free_queue_item(t_list *curr)
{
	free (curr->content);
	free (curr);
}

void		del_queue(t_list **lst)
{
	t_list 	*curr;
	t_list	*prev;

	curr = *lst;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
		free_queue_item(prev);
	}
}

void		free_queue(t_qwrap **rw)
{
	del_queue((*rw)->queue);
	free (*rw);
}
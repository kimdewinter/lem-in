/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_route_finding.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 19:51:48 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/09 12:46:23 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

// void		free_subpath_path(t_room **path, size_t len)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		if (path[i])
// 			free (path[i]);
// 		i++;
// 	}
// }

// void		free_subpath(t_subpath **pt)
// {
// 	if ((*pt)->bitconj)
// 		free ((*pt)->bitconj);
// 	// if ((*pt)->path)
// 	// 	free_subpath_path((*pt)->path, (*pt)->len);
// }

/* Doesn't free subpaths because they are assigned to rooms by now */
void		free_queue_item(t_list *curr)
{
	if (curr->content)
		free ((t_queue *)curr->content);
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
		if (prev)
		{
			if (prev->content)
				free_queue_item(prev);
			free (prev);
		}
	}
}

void		free_queue(t_qwrap **rw)
{
	if ((*rw)->queue)
	{
		del_queue((*rw)->queue);
		free ((*rw)->queue);
	}
	if (*rw)
		free (*rw);
}
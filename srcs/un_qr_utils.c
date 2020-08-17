/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_qr_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 15:28:26 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/13 16:11:19 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			free_q_un(t_conn_wrap **qr)
{
	t_connection	*prev;
	t_connection	*iter;

	prev = NULL;
	iter = *(*qr)->q;
	while (iter)
	{
		prev = iter;
		iter = iter->next;
		remove_q_item_un(*qr, prev);
	}
	if ((*qr)->visited)
	{
		free((*qr)->visited);
		(*qr)->visited = NULL;
	}
	if ((*qr)->q)
	{
		free((*qr)->q);
		(*qr)->q = NULL;
	}
	if (*qr)
		free(*qr);
}

ssize_t			setup_q_un(t_conn_wrap **qr, t_map *map)
{
	(*qr) = (t_conn_wrap *)malloc(sizeof(t_conn_wrap));
	if (*qr)
	{
		(*qr)->q = (t_connection **)malloc(sizeof(t_connection *));
		if ((*qr)->q)
		{
			*(*qr)->q = NULL;
			if (bite_alloc(&(*qr)->visited, map) == EXIT_SUCCESS)
			{
				(*qr)->items = 0;
				return (EXIT_SUCCESS);
			}
			free((*qr)->q);
			(*qr)->q = NULL;
		}
		free(*qr);
		(*qr) = NULL;
	}
	return (EXIT_FAILURE);
}

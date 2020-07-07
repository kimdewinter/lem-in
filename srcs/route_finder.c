/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 14:33:23 by kim           #+#    #+#                 */
/*   Updated: 2020/07/07 13:45:19 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t				add_path_to_dst(t_qwrap *qr, t_queue *curr,
t_map *map)
{
	t_subpath	*new;

	new = NULL;
	if (curr->src == map->end && qr->round == 1)
	{
		if (create_new_path(&new, NULL, map->end, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (add_path(qr, curr, new, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		if (add_path(qr, curr, curr->path, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static size_t			execute_queue(t_qwrap *qr, t_map *map)
{
	t_queue	*iter;

	iter = *(qr->queue);
	while (iter)
	{
		iter->handled = 1;
		if (add_path_to_dst(qr, iter, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		iter = iter->next;
		if (iter == NULL)
		{
			if (adjust_queue(qr, map, qr->items) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			iter = *(qr->queue);
		}
	}
	free (qr->queue);
	free (qr);
	exit (0);
	return (EXIT_SUCCESS);
}

size_t			find_routes(t_map *map)
{
	t_qwrap		*queue;

	if (setup_queue(&queue, map) == EXIT_SUCCESS &&
		execute_queue(queue, map) == EXIT_SUCCESS &&
		assemble_all_routes(map) == EXIT_SUCCESS)
	{
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

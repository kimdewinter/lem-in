/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_setup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 13:45:50 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/21 21:04:44 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		is_not_junction(t_room *tmp, t_room *prev, t_map *map)
{
	if (prev == NULL)
	{
		if (tmp->is_conj == 0 && tmp != map->start)
			return (1);
		return (0);
	}
	if ((tmp->checked == 1 && tmp->is_conj == 0)
	|| (tmp->checked == 0 && is_junction(prev, tmp, map) == 0))
		return (1);
	return (0);
}

static ssize_t	create_queue(t_qwrap **qr, t_map *map)
{
	*qr = (t_qwrap *)malloc(sizeof(t_qwrap));
	if (*qr)
	{
		(*qr)->queue = (t_queue **)malloc(sizeof(t_queue *));
		(*qr)->items = 0;
		(*qr)->last = NULL;
		(*qr)->round = 1;
		if ((*qr)->queue)
		{
			*((*qr)->queue) = NULL;
			map->end->weight = (*qr)->round;
			if (bite_alloc(&((*qr)->visited), map) == EXIT_SUCCESS)
			{
				if (bite_alloc(&((*qr)->in_queue), map) == EXIT_SUCCESS)
					return (EXIT_SUCCESS);
				free ((*qr)->visited);
			}
			free ((*qr)->queue);
		}
		free (*qr);
		*qr = NULL;
	}
	return (EXIT_FAILURE);
}

ssize_t		add_nb_to_queue_setup(t_qwrap *qr, t_room *nb, t_map *map)
{
	t_room		*dst;
	t_subpath	*new;
	int			valid;

	new = NULL;
	dst = NULL;
	if (create_new_path(&new, NULL, map->end, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	valid = find_next_path(&dst, &new, nb, map->end, map);
	if (valid == 0)
		return (EXIT_SUCCESS);
	if (room_in_bitfield(dst, qr->visited) == 1)
	{
		if (solve_queue_conflict(qr, new, dst) == 0)
		{
			delete_path(&new);
			return (EXIT_SUCCESS);
		}
	}
	if (add_to_queue(qr, map->end, dst, new) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

ssize_t		setup_queue(t_qwrap **qr, t_map *map)
{
	size_t	i;

	i = 0;
	if (create_queue(qr, map) == EXIT_SUCCESS)
	{
		while (i < map->end->neighbours_len)
		{
			if (add_nb_to_queue_setup(*qr, map->end->neighbours[i], map)
			== EXIT_FAILURE)
				return (EXIT_FAILURE);
			i++;
		}
		map->end->dead_end = 1;
		(*qr)->round++;
		print_queue(*qr);
		exit (0);
	}
	return (EXIT_FAILURE);
}


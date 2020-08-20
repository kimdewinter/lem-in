/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_update_q_add_nbs.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 12:22:23 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/20 12:12:30 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	setup_add(t_connection *tmp, t_room *start,
BITFIELD_TYPE **atq, t_map *map)
{
	if (bite_alloc(atq, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	setup_conn(tmp, start);
	return (EXIT_SUCCESS);
}

static ssize_t	free_and_return(BITFIELD_TYPE **atq, ssize_t ret)
{
	free(*atq);
	*atq = NULL;
	return (ret);
}

static void		setup_and_set(t_connection *tmp, t_room *start, t_room *nb)
{
	setup_conn(tmp, start);
	set_conn(tmp, nb);
}

static void		init(size_t *i, size_t *added)
{
	*i = 0;
	*added = 0;
}

ssize_t			un_add_nbs_to_queue(t_room *start, t_conn_wrap *qr,
t_map *map, int *changed)
{
	size_t			i;
	t_connection	tmp;
	BITFIELD_TYPE	*atq;
	size_t			added;

	// printf("ADD NBS TO QUEUE\n");
	init(&i, &added);
	if (setup_add(&tmp, start, &atq, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (i < start->neighbours_len)
	{
		setup_and_set(&tmp, start, start->neighbours[i]);
		if (check_conn(&tmp, &i, changed, map) == 1
		&& room_in_bitfield(tmp.dst, qr->visited) == 0)
		{
			if (room_in_bitfield(tmp.dst, atq) == 1)
			{
				*changed = 1;
				i -= solve_queue_conflict(qr, &tmp, map, &added);
			}
			if (add_q_item_un(qr, &tmp, &added, atq) == EXIT_FAILURE)
				return (free_and_return(&atq, EXIT_FAILURE));
		}
		i++;
	}
	return (free_and_return(&atq, EXIT_SUCCESS));
}

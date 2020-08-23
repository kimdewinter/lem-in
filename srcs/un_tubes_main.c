/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_tubes_main.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 16:16:18 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/23 10:57:25 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t			remove_unnecessary_tubes(t_map *map, int *changed)
{
	t_conn_wrap		*qr;

	*changed = 0;
	if (setup_q_un(&qr, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (un_add_start_nbs_to_q(map->start, qr, map, changed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (execute_queue_un(qr, map, changed) == EXIT_FAILURE)
	{
		free_q_un(&qr);
		return (EXIT_FAILURE);
	}
	free_q_un(&qr);
	return (EXIT_SUCCESS);
}

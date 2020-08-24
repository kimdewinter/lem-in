/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_best_option_route.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:47:55 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/24 14:49:48 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void		switch_if_better(ssize_t *best, ssize_t j, t_room *start)
{
	if (start->neighbours[j]->dist_to_end
	< start->neighbours[*best]->dist_to_end)
		*best = j;
	else if (start->spe == 1
	&& start->neighbours[j] == start->spe_start
	&& start->neighbours[j]->dist_to_end ==
	start->neighbours[*best]->dist_to_end)
		*best = j;
	else if (start->neighbours[j]->dist_to_end
	== start->neighbours[*best]->dist_to_end
	&& start->neighbours[*best]->sps == 1
	&& start->neighbours[j]->sps == 0)
		*best = j;
}

void			find_best_option(t_room *start, BITFIELD_TYPE *visited,
ssize_t *i)
{
	ssize_t	best;
	ssize_t	j;

	*i = 0;
	j = *i;
	best = -1;
	while ((size_t)j < start->neighbours_len)
	{
		if (room_in_bitfield(start->neighbours[j], visited) == 0
		&& start->neighbours[j]->dist_to_end >= 0)
		{
			if (best == -1)
				best = j;
			else
				switch_if_better(&best, j, start);
		}
		j++;
	}
	*i = best;
}

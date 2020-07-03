/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_checks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 14:01:31 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/03 14:06:29 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int				check_length_spe(t_subpath *path, t_room *nb,
t_map *map)
{
	ssize_t	j;

	j = nb->num_options - 1;
	while (j >= 0)
	{
		if (nb->routes[j]->conj == map->end)
		{
			if (path->len + 1 < nb->routes[j]->len)
				return (1);
			return (0);
		}
		j--;
	}
	return (1);
}

size_t			is_viable_for_path(t_map *map, t_queue *item,
t_room *nb, t_subpath *path)
{
	if (nb != item->src
	&& nb != path->conj
	&& (!(item->dst->sps == 1 && nb != map->start)))
	{
		if (nb->weight == 0 && nb != map->start)
			return (1);
		if (room_in_bitfield(path->conj, nb->bitconj) == 1)
		{
			if (check_length(path, nb) == 1)
				return (1);
			return (0);
		}
		if (nb->spe == 1)
		{
			if (check_length_spe(path, nb, map) == 1)
				return (1);
			return (0);
		}
		return (1);
	}
	return (0);
}

int			check_length(t_subpath *new_path, t_room *curr)
{
	ssize_t	j;
	size_t	found;

	j = curr->num_options - 1;
	found = 0;
	while (j >= 0)
	{
		if (curr->routes[j]->conj == new_path->conj)
		{
			found++;
			if ((new_path->segment_len + 1) > curr->routes[j]->segment_len)
				return (0);
			else if ((new_path->segment_len + 1) == curr->routes[j]->segment_len
			&& curr->routes[j]->sp == 1)
				return (0);
		}
		j--;
	}
	if (found == 0)
		return (0);
	return (1);
}
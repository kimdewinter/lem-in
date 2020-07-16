/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_conflicts.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 13:21:10 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/16 21:33:29 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int			is_nb_of_src(t_room *src, t_room *nb)
{
	size_t	i;

	i = 0;
	while (i < src->neighbours_len)
	{
		if (src->neighbours[i] == nb)
			return (1);
		i++;
	}
	return (0);
}

int			is_junction(t_room *src, t_room *dst, t_map *map)
{
	size_t	i;
	int		viable;

	i = 0;
	dst->checked = 1;
	if (dst->num_options != 0 || dst == map->start || dst == map->end)
	{
		dst->is_conj = 1;
		return (1);
	}
	viable = 0;
	printf("Candidate %s %lu\n", dst->name, dst->weight);
	i = 0;
	while (i < dst->neighbours_len)
	{
		printf("nb checked: %s %lu\n", dst->neighbours[i]->name,
		dst->neighbours[i]->weight); 
		if (dst->neighbours[i]->dead_end == 0
		&& dst->neighbours[i] != dst
		&& dst->neighbours[i] != src
		&& ((is_nb_of_src(src, dst->neighbours[i]) == 1
		&& (dst->neighbours[i]->neighbours_len > 3
		&& dst->neighbours_len > 3))
		|| is_nb_of_src(src, dst->neighbours[i])== 0))
		{
			viable++;
			if (viable > 1)
			{
				printf("Is junction\n");
				dst->is_conj = 1;
				return (1);
			}
		}
		i++;
	}
	dst->is_conj = 0;
	printf("Not junction\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_conflicts.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 13:21:10 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/21 20:55:09 by lravier       ########   odam.nl         */
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

int			check_triangles(t_room *src, t_room *dst, t_room *nb)
{
	printf("Check triangles src %s dst %s nb %s\n", src->name, dst->name,
	nb->name);
	if((is_nb_of_src(src, nb) == 1
	&& (nb->neighbours_len > 3
	&& dst->neighbours_len > 3))
	|| is_nb_of_src(src, nb) == 0)
	{
		return (1);
	}
	add_to_bitfield(dst, nb->unavailable);
	add_to_bitfield(nb, dst->unavailable);
	printf("Is triangle\n");
	return (0);
}

int			is_junction(t_room *src, t_room *dst, t_map *map)
{
	size_t	i;
	int		viable;
	// t_room	*single_nb;

	i = 0;
	// single_nb = NULL;
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
		&& room_in_bitfield(dst->neighbours[i], dst->unavailable) == 0
		&& check_triangles(src, dst, dst->neighbours[i]) == 1)
		{
			// single_nb = dst->neighbours[i];
			printf("Viable %s\n", dst->neighbours[i]->name);
			viable++;
			if (viable > 1)
			{
				printf("Is junction\n");
				dst->is_conj = 1;
				return (1);
			}
		}
		// add_to_bitfield(dst->neighbours[i], dst->unavailable);
		i++;
	}
	// add_to_bitfield(dst, single_nb->unavailable);
	// add_to_bitfield(single_nb, dst->unavailable);
	// printf("NOT CONJ %s %s\n", dst->name, single_nb->name);
	dst->is_conj = 0;
	printf("Not junction\n");
	return (0);
}

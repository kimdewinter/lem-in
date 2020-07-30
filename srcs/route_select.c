/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_select.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 16:02:23 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/29 16:02:23 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int	same_with_extra_steps(t_subpath *pt1, t_subpath *pt2, t_map *map)
{
	size_t			i;
	BITFIELD_TYPE 	mask;

	i = 0;
	while (i < map->bitfield_len)
	{
		mask = (pt1->bitconj[i] ^ pt2->bitconj[i]);
		if ((pt1->bitconj[i] & mask) != (BITFIELD_TYPE)0)
			return (0);
		i++;
	}
	print_path(pt1);
	print_path(pt2);
	/* Adjust num options! */
	printf("Same with extra steps\n");
	map->num_routes--;
	return (1);
}

static int	adds_compatibility(t_subpath *pt1, t_subpath *pt2, t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->start->num_options)
	{
		if ((pt1->compatible_paths[i] == 0 && pt2->compatible_paths[i] == 1)
		&& map->start->routes[i] != NULL)
			return (1);
		i++;
	}
	map->num_routes--;
	return (0);
}

ssize_t		select_paths(t_map *map, int *changed)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	print_paths(map->start);
	while (i < map->start->num_options)
	{
		j = i + 1;
		while (j < map->start->num_options)
		{
			if (map->start->routes[i] != NULL
			&& map->start->routes[j] != NULL
			&& map->start->routes[i]->end == map->start->routes[j]->end)
			{
				if (same_with_extra_steps(map->start->routes[i],
				map->start->routes[j], map)== 1)
				{
					*changed = 1;
					free (map->start->routes[j]);
					map->start->routes[j] = NULL;
				}
				else if (same_with_extra_steps(map->start->routes[j],
				map->start->routes[i], map) == 1)
				{
					*changed = 1;
					free (map->start->routes[i]);
					map->start->routes[i] = NULL;
				}
			}
			if (map->start->routes[i] != NULL
			&& map->start->routes[j] != NULL
			&& map->start->routes[i]->start == map->start->routes[j]->start)
			{
				if (adds_compatibility(map->start->routes[i],
				map->start->routes[j], map) == 0)
				{
					*changed = 1;
					free (map->start->routes[j]);
					map->start->routes[j] = NULL;
				}
			}
			j++;
		}
		i++;
	}
	print_paths(map->start);
}
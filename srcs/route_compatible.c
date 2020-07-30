/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_compatible.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 16:59:04 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/28 16:59:04 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

// static ssize_t	comp_alloc(BITFIELD_TYPE **dst, size_t size)
// {
// 	size_t	i;

// 	*dst =
// 		(BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * size);
// 	if (*dst == NULL)
// 		return (handle_err_biter(1, "bite_alloc\n"));
// 	printf("After alloc actual\n");
// 	i = 0;
// 	while (i < size)
// 	{
// 		(*dst)[i] = (BITFIELD_TYPE)0;
// 		printf("Set to 0\n");
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }

void			add_compatible(size_t index, t_subpath *path)
{
	path->compatible_paths[index / BITFIELD_SIZE] |=
	((BITFIELD_TYPE)1 << (63 - index % BITFIELD_SIZE));	
}

static int		has_overlap(t_subpath *src, t_subpath *dst,
size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if ((src->bitconj[i] & dst->bitconj[i])
		!= (BITFIELD_TYPE)0)
			return (1);
		i++;
	}
	return (0);
}

static int		is_compatible(t_subpath	*pt1, t_subpath *pt2, t_map *map)
{
	if ((pt1->start == pt2->start) || (pt1->end == pt2->end))
		return (0);
	else if (has_overlap(pt1, pt2, map->bitfield_len) == 1)
		return (0);
	else
	{
		pt1->max_compatible++;
		pt2->max_compatible++;
		return (1);
	}
}

static ssize_t	setup_array(int **arr, size_t size)
{
	size_t	i;

	i = 0;
	*arr = (int *)malloc(size * sizeof(int));
	if (*arr)
	{
		while (i < size)
		{
			(*arr)[i] = 0;
			i++;
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

ssize_t			setup_compatibility(t_map *map)
{
	size_t	i;

	// printf("Setup compatibility\n");
	// map->bitfield_len_paths = (map->start->num_options / BITFIELD_SIZE) + 1;
	i = 0;
	// printf("num options %lu\npath bite %lu\n", map->start->num_options,
	// map->bitfield_len_paths);
	while (i < map->start->num_options)
	{
		// printf("i: %lu\n", i);
		// printf("%p\n", map->start->routes[i]);
		// if (comp_alloc(&(map->start->routes[i]->compatible_paths),
		// map->bitfield_len_paths)
		if (map->start->routes[i] != NULL)
		{
			map->start->routes[i]->max_compatible = 0;
			if (setup_array(&(map->start->routes[i]->compatible_paths),
			map->start->num_options)
			== EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	// printf("After setup\n");
	return (EXIT_SUCCESS);
}

ssize_t			set_compatibility(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (setup_compatibility(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (i < map->start->num_options)
	{
		j = i + 1;
		// printf("i: %lu\n", i);
		// printf("Main path:\n");
		// print_path(map->start->routes[i]);
		if (map->start->routes[i] != NULL)
		{
			while (j < map->start->num_options)
			{
				// printf("j: %lu\n", j);
				// printf("Compatible check\n");
				// print_path(map->start->routes[j]);
				if (map->start->routes[j] != NULL &&
				is_compatible(map->start->routes[i], map->start->routes[j], map)
				== 1)
				{
					// printf("Compatible\n");
					map->start->routes[i]->compatible_paths[j] = 1;
					map->start->routes[j]->compatible_paths[i] = 1;
					// add_compatible(i, map->start->routes[j]);
					// add_compatible(j, map->start->routes[i]);
				}
				j++;
			}
		}
		i++;
	}
	// printf("After\n");
	// size_t		x;
	// // uint64_t 	mask;
	// size_t		iter;
	// int total;

	// total = 0;
	// iter = 0;
	// x = 0;
	// // mask = (BITFIELD_TYPE)1;
	// while (x < map->bitfield_len_paths)
	// {
	// 	// mask = (BITFIELD_TYPE)1;
	// 	iter = 0;
	// 	while (iter < 64)
	// 	{
	// 		if (((map->start->routes[0]->compatible_paths[x] & (1 << iter)) != 0)
	// 		&& ((map->start->routes[1]->compatible_paths[x] & (1 << iter)) != 0)
	// 		&& ((map->start->routes[2]->compatible_paths[x] & (1 << iter))) != 0)
	// 			total++;
	// 		iter++;
	// 	}
	// 	x++;
	// }
	// printf("Total compatible paths left %d\n", total);
	// exit (0);
	return (EXIT_SUCCESS);
}
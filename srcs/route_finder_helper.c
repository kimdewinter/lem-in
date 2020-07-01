/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder_helper.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 16:21:39 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/28 14:24:44 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"


int			has_path_to_conj(t_room *curr, t_room *conj)
{
	// if (curr->sps == 1)
	// 	return (1);
	printf("Has path to conj: %s curr: %s\n", conj->name, curr->name);
	if ((curr->bitconj[conj->room_i / BITFIELD_SIZE] &
	((BITFIELD_TYPE)1 << (63 - conj->room_i % BITFIELD_SIZE))) != (BITFIELD_TYPE)0)
	{
		printf("Yes\n");
		return (1);
	}
	printf("no\n");
	return (0);
}

// int			is_path_to_conj(t_subpath *pt, t_room *conj)
// {
// 	printf("is path to con\n");
// 	if ((pt->bitconj[conj->room_i / BITFIELD_SIZE] &
// 	((BITFIELD_TYPE)1 << (63 - conj->room_i % BITFIELD_SIZE))) != (BITFIELD_TYPE)0)
// 	{
// 		printf("Yes\n");
// 		return (1);
// 	}
// 	return (0);
// }


// void				replace_path(t_subpath *pt, t_room *dst)
// {
// 	ssize_t	j;

// 	j = dst->num_options - 1;
// 	while (j >= 0)
// 	{
// 		if (dst->routes[j]->conj == pt->conj)
// 		{
// 			if (dst->routes[j])
// 				free (dst->routes[j]);
// 			dst->routes[j] = pt;
// 		}
// 		j--;
// 	}
// }

// size_t				add_subpath(t_queue *curr, t_subpath **pt, t_map *map)
// {
// 	if (has_path_to_conj(curr->dst, (*pt)->conj) == 1)
// 	{
// 		printf("Has ptc\n");
// 		if (check_length(*pt, curr->dst) == 1)
// 		{
// 			replace_path(*pt, curr->dst);
// 			curr->added = 0;
// 		}
// 	}
// 	if (curr->dst != map->start)
// 		add_bite_conj(curr->dst, (*pt)->conj);
// 	(*pt)->added_this_turn = 1;
// 	printf("src %s\ndst %s\n", curr->dst->name, curr->src->name);
// 	printf("num options %lu\nsize %lu\n", curr->dst->num_options, curr->dst->routes_size);
// 	if (curr->dst->num_options <= curr->dst->routes_size)
// 	{
// 		if (increase_routes_size(&curr->dst, map) == EXIT_FAILURE)
// 			return (EXIT_FAILURE);
// 	}
// 	curr->dst->routes[curr->dst->num_options] = *pt;
// 	curr->dst->num_options++;
// 	return (EXIT_SUCCESS);
// }

// size_t			add_subpath(t_room *src, t_room *dst, t_subpath **pt, t_map *map)
// {
// 	ssize_t		i;

// 	i = dst->num_options - 1;
// 	(void)src;
// 	(*pt)->added_this_turn = 1;
// 	(*pt)->src = src;
// 	/* Make sure we overwrite non-single paths to conj if we're adding an sp
// 	with the same length */
// 	printf("ADD SUBPATH\nDST: %s\nSRC: %s\nPATH: \n", dst->name, src->name);
// 	print_path(*pt);
// 	printf("\n\n\n");
// 	if ((*pt)->path != NULL && (has_path_to_conj(dst, (*pt)->conj) == 1))
// 	{
// 		printf("\n\nIN ADD SUBPATH has path to conj\n\n");
// 		while (i >= 0)
// 		{
// 			if (dst->routes[i])
// 			{
// 				if (dst->routes[i]->conj == (*pt)->conj)
// 				{
// 					if ((*pt)->segment_len < dst->routes[i]->segment_len)
// 					{
// 						printf("Replacing path\n");
// 						printf("subpath %p\n", *pt);
// 						print_path(*pt);
// 						print_path(dst->routes[i]);
// 						free (dst->routes[i]);
// 						dst->routes[i] = (*pt);
// 					}
// 					else
// 					{
// 						printf("KILLING SRC %s\n", (*pt)->path[(*pt)->start + 1]->name);
// 						print_path(*pt);
// 						(*pt)->path[(*pt)->start + 1]->dead_end = 1;
// 						// dst->viable_nbs--;
// 						free (*pt);
// 						*pt = NULL;
// 					}
// 				}
// 			}
// 			i--;
// 		}
// 	}
// 	else
// 	{
// 		if (dst->num_options < dst->routes_size)
// 		{
// 			dst->routes[dst->num_options] = (*pt);
// 			dst->num_options++;
// 		}
// 		else
// 		{
// 			if (increase_routes_size(&dst, map) == EXIT_FAILURE)
// 				return (EXIT_FAILURE);
// 			dst->routes[dst->num_options] = (*pt);
// 			dst->num_options++;
// 		}
// 	}
// 	printf("after adding\n");
// 	return (EXIT_SUCCESS);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_adding.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:34:22 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/29 11:14:38 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"




// size_t	add_nodes_until_new_conj(t_room **new_dst, t_queue *item, t_subpath *path, 
// t_map *map)
// {
// 	t_room	*nb;
// 	t_room	*prev;
// 	t_room	*src;
// 	size_t	i;
// 	int		found;

// 	i = 0;
// 	found = 0;
// 	prev = item->dst;
// 	nb = item->dst;
// 	src = item->src;
// 	if (add_to_path(path, item->dst, map) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	if (nb->is_conj == 0)
// 		nb->dead_end = 1;
// 	while (nb->is_conj == 0 && nb != map->start)
// 	{
// 		prev = nb;
// 		i = 0;
// 		found = 0;
// 		while (i < nb->neighbours_len && nb->is_conj == 0)
// 		{
// 			// printf("i: %lu\n", i);
// 			// printf("Prev: %s Src: %s NB: %s Dead end: %d\n", prev->name, item->src->name,
// 			// nb->neighbours[i]->nb->name, nb->neighbours[i]->nb->dead_end);
// 			if (nb->neighbours[i]->nb->dead_end == 0
			// && nb->neighbours[i]->nb != prev
			// && nb->neighbours[i]->nb != src
			// && nb->neighbours[i]->nb != map->end
			// && nb->neighbours[i]->available == 1)
// 			{
// 				printf("NB FOUND %s is conj: %d\n", nb->neighbours[i]->nb->name, nb->neighbours[i]->nb->is_conj);
// 				nb = nb->neighbours[i]->nb;
// 				if (nb->is_conj == 0)
// 					nb->dead_end = 1;
// 				nb->viable_nbs--;
// 				found = 1;
// 				src = prev;
// 				break;
// 			}
// 			i++;
// 		}
// 		if (found == 0)
// 			return (EXIT_SUCCESS);
// 		if (found == 1 && nb->is_conj == 0)
// 		{
// 			if (add_to_path(path, nb, map) == EXIT_FAILURE)
// 				return (EXIT_FAILURE);
// 		}
// 	}
// 	// printf("NEW DST: %s\n", nb->name);
// 	*new_dst = nb;
// 	return (EXIT_SUCCESS);
// }

// size_t		add_new_subp_path(t_subpath **new, t_map *map)
// {
// 	size_t		size;

// 	size = (map->rooms->count * 100) / ((100 / INIT_ROUTE_PERC) * 100);
// 	if (size == 0)
// 		size = map->rooms->count;
// 	(*new)->path = new_path(size);
// 	if ((*new)->path)
// 	{
// 		(*new)->size = size;
// 		(*new)->start = size - 1;
// 		return (EXIT_SUCCESS);
// 	}
// 	free (*new);
// 	(*new) = NULL;
// 	return (EXIT_FAILURE);
// }

// int			sp_path_shorter(t_subpath *pt, t_room *curr)
// {
// 	ssize_t		j;
// 	size_t		index_long;
// 	t_subpath	*longer;

// 	printf("CHECK WHETHER THIS WAY IS SHORTER\n");
// 	print_path(pt);
// 	j = curr->num_options - 1;
// 	index_long = 0;
// 	longer = NULL;
// 	while (j >= 0 && curr->routes[j]->added_this_turn == 1)
// 	{
// 		if (curr->routes[j]->conj == pt->conj && curr->routes[j]->sp == 1)
// 		{
// 			printf("seg len dst %lu seg len to add %lu\n", pt->segment_len + 1,
// 			curr->routes[j]->segment_len);
// 			print_path(curr->routes[j]);
// 			if (pt->segment_len + 1 < curr->routes[j]->segment_len)
// 				return (0);
// 			else
// 			{
// 				longer = curr->routes[j];
// 				index_long = j;
// 			}
// 		}
// 		j--;
// 	}
// 	(void)index_long;
// 	print_path(longer);
// 	printf("Yes\n");
// 	return (1);
// }

// int			has_path_to_path_junction(t_room *dst, t_room *curr, t_map *map)
// {
// 	size_t	i;

// 	i = 0;
// 	printf("Share a common previous junction\n");
// 	while (i < map->bitfield_len)
// 	{
// 		printf("Dst conj: %lu curr conj %lu\n", dst->bitconj[i], curr->bitconj[i]);
// 		if (dst->bitconj[i] != 0 && curr->bitconj[i] != 0)
// 		{
// 			if (((dst->bitconj[i] ^ ((BITFIELD_TYPE)1 << (63 - map->end->room_i % BITFIELD_SIZE)))
// 			& (curr->bitconj[i] ^ ((BITFIELD_TYPE)1 << (63 - map->end->room_i % BITFIELD_SIZE)))) != 0)
// 			{
// 				printf("Yes\n");
// 				return (1);
// 			}
// 		}
// 		i++;
// 	}
// 	printf("No\n");
// 	return (0);
// }

// size_t		add_new_conj_path(t_queue *item, t_room *dst, t_room *src,
// t_subpath *pt, t_map *map)
// {
// 	t_subpath	*new;

// 	new = NULL;
// 	(void)item;
// 	printf("ADD NEW CONJ PATH\n");
// 	/* Checks if room has path to previous junction, which only happens if there was
// 	a direct path added to it THIS round */
// 	if (pt && pt->conj)
// 		printf("Conj: %s\n", pt->conj->name);
// 	if (create_new_path(&new, pt, src, map) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	if (add_subpath(src, dst, &new, map) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	printf("CONJ WE'RE ADDING %s TO %s\n", src->name, dst->name);
// 	if (dst != map->start)
// 		add_bite_conj(dst, src);
// 	// printf("add new conj path\n");
// 	// print_path(new);
// 	return (EXIT_SUCCESS);
// }

// t_room		*find_only_neighbour(t_room *src)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < src->neighbours_len)
// 	{
// 		if (src->neighbours[i]->available == 1)
// 			return (src->neighbours[i]->nb);
// 		i++;
// 	}
// 	return (NULL);
// }

// size_t		add_to_this_conj_path(t_queue *item, t_room *dst, t_room *src,
// t_subpath *pt, t_map *map)
// {
// 	// t_subpath	*new;
// 	printf("ADD TO THIS CONJ\n");
// 	(void)item;
// 	if (add_to_path(pt, src, map) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	pt->sp = 1;
// 	// print_path(pt);
// 	// exit (0);
// 	if (add_subpath(pt->conj, dst, &pt, map) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	// print_paths(dst);
// 	printf("CONJ WE'RE ADDING %s TO %s\n", src->name, dst->name);
// 	if (dst != map->start)
// 		add_bite_conj(dst, src);
// 	// print_path(pt);
// 	// exit (0);
// 	return (EXIT_SUCCESS);
// }

// size_t		add_to_conj_path(t_queue *item, t_room *dst, t_room *src,
// t_subpath *pt, t_map *map)
// {
// 	t_subpath	*new;
// 	t_room		*new_dst;

// 	new_dst = NULL;
// 	(void)dst;
// 	if (create_new_path(&new, pt, src, map) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	new->sp = 1;
// 	if (item->dst->is_conj == 0)
// 	{
// 		if (add_nodes_until_new_conj(&new_dst, item, new, map) == EXIT_FAILURE)
// 			return (EXIT_FAILURE);
// 	}
// 	if (!new_dst)
// 		return (EXIT_SUCCESS);
// 	if (add_subpath(src, new_dst, &new, map) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	if (new != NULL && new_dst != map->start)
// 	{
// 		printf("CONJ WE'RE ADDING %s TO %s\n", new->conj->name, new_dst->name);
// 		add_bite_conj(new_dst, new->conj);
// 	}
// 	if (new == NULL)
// 		item->added = 0;
// 	item->dst = new_dst;
// 	item->path = new;
// 	item->new_conj = 0;
// 	return (EXIT_SUCCESS);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_add_nodes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 13:27:58 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/13 13:13:22 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t		nb_is_viable(t_room *prev, t_room *nb, t_subpath *pt, 
int *found)
{
	if (nb->dead_end == 0
	&& nb != prev
	&& nb != pt->conj)
	{
		*found = 1;
		return (1);
	}
	return (0);
}

static ssize_t		add_node_to_path(t_room **nb, t_subpath **path, t_map *map)
{
	if ((*nb)->is_conj == 0)
	{
		if (add_to_path(*path, *nb, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		(*nb)->dead_end = 1;
	}
	return (EXIT_SUCCESS);
}

static void			set_nb_attributes(t_room **curr, t_room *nb, t_room **prev,
t_map *map)
{
	*prev = *curr;
	*curr = nb;
	if (nb != map->start && nb->weight == 0)
		nb->weight = (*prev)->weight + 1;	
}

static void			set_item_attributes(t_queue **item, t_room **nb,
t_room *prev, t_map *map)
{
	if (*nb != map->start && (*nb)->weight == 0)
		(*nb)->weight = prev->weight + 1;
	(*item)->dst = *nb;	
}

ssize_t				add_nodes_to_path(t_queue *item, t_subpath **path,
t_map *map, int *add)
{
	t_room *nb;
	t_room *prev;
	size_t	i;
	int		found;

	prev = NULL;
	nb = item->dst;
	if (nb->weight == 0 && nb != map->start)
		nb->weight = item->dst->weight;
	while (nb->is_conj == 0 && nb != map->start)
	{
		i = 0;
		found = 0;
		while (i < nb->neighbours_len)
		{
			if (nb_is_viable(prev, nb->neighbours[i], *path, &found) == 1)
			{
				if (add_node_to_path(&nb, path, map) == EXIT_FAILURE)
					return (EXIT_FAILURE);
				set_nb_attributes(&nb, nb->neighbours[i], &prev, map);
				break;
			}
			i++;
		}
		if (found == 0)
			break;
	}
	if (found == 1)
		set_item_attributes(&item, &nb, prev, map);
	else
		*add = 0;
	return (EXIT_SUCCESS);
}

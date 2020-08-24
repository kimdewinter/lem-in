/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_dead_ends.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 12:48:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/24 13:20:53 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void		remove_dead_path(t_room *tmp, t_map *map)
{
	t_room	*prev;
	t_room	*curr;
	size_t	i;
	int		first;

	prev = tmp;
	curr = tmp;
	i = 0;
	first = 1;
	while (i < curr->neighbours_len)
	{
		if (curr->neighbours[i]->neighbours_len == 2
		&& curr->neighbours[i] != map->end
		&& curr->neighbours[i] != map->start
		&& curr->neighbours[i] != prev)
		{
			prev = curr;
			curr = curr->neighbours[i];
			if (first == 1)
			{
				del_tube(prev, curr, map);
				del_tube(curr, prev, map);
				first = 0;
			}
			i = 0;
		}
		i++;
	}
	del_tube(curr, prev, map);
	del_tube(prev, curr, map);
}

void		remove_dead_ends(t_map *map)
{
	size_t	i;
	t_table	*table;
	t_room	*tmp;

	tmp = NULL;
	table = map->rooms;
	i = 0;
	while (i < table->size)
	{
		if (table->entries[i] != NULL)
		{
			tmp = (t_room *)table->entries[i]->val;
			if (tmp->neighbours_len == 1
			&& tmp != map->end
			&& tmp != map->start)
				remove_dead_path(tmp, map);
		}
		i++;
	}
}
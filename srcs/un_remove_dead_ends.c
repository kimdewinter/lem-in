/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_remove_dead_ends.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 11:20:18 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/17 11:24:02 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int		is_dead_end_first(t_room *curr)
{
	if (curr->neighbours_len == 0 || curr->conns_to == 0)
		return (1);
	if (curr->neighbours_len == 1)
	{
		if (curr->conns_to == 1 && is_mutual_conn(curr, curr->neighbours[0])
		== 1)
			return (1);
	}
	return (0);
}

static int		is_dead_end_cont(t_room *curr)
{
	if (curr->neighbours_len > 2)
		return (0);
	if (curr->neighbours_len == 1)
	{
		if (curr->conns_to == 1)
			return (1);
		if (curr->conns_to == 2)
		{
			if (is_mutual_conn(curr, curr->neighbours[0]) == 1)
				return (1);
		}
	}
	if (curr->neighbours_len == 2)
	{
		if (curr->conns_to == 1)
			return (1);
		if (curr->conns_to == 2)
		{
			if (is_mutual_conn(curr, curr->neighbours[0]) == 1
			|| is_mutual_conn(curr, curr->neighbours[1]) == 1)
				return (1);
		}
	}
	return (0);
}

static void		remove_dead_end_from_nbs(t_room *dead, t_map *map)
{
	size_t	i;
	size_t	j;
	t_room	*nb;

	i = 0;
	while (i < dead->neighbours_len)
	{
		if (dead->neighbours[i] != NULL)
		{
			j = 0;
			nb = dead->neighbours[i];
			while (j < nb->neighbours_len)
			{
				if (nb->neighbours[j] == dead)
				{
					j -= handle_nowhere_to_go(nb, dead, map);
					break ;
				}
				j++;
			}
		}
		i++;
	}
}

static void		remove_dead_path(t_room **tmp, t_map *map)
{
	t_room	*prev;
	size_t	j;

	prev = *tmp;
	if (*tmp == NULL
	|| (*tmp)->neighbours == NULL
	|| (*tmp)->neighbours_len == 0)
		return ;
	*tmp = *((*tmp)->neighbours);
	j = 0;
	while (*tmp != NULL
	&& is_dead_end_cont(*tmp) == 1
	&& *tmp != map->start
	&& *tmp != map->end)
	{
		j = 0;
		if ((*tmp)->neighbours[j] == prev)
			j++;
		prev = *tmp;
		if (j < (*tmp)->neighbours_len)
			*tmp = (*tmp)->neighbours[j];
		else
			break ;
	}
	remove_dead_end_from_nbs(prev, map);
}

void			remove_dead_ends(t_map *map, int *changed)
{
	size_t	i;
	t_room	*tmp;

	i = 0;
	while (i < map->rooms->size)
	{
		if (map->rooms->entries[i] != NULL)
		{
			tmp = ((t_room *)map->rooms->entries[i]->val);
			if (tmp != map->start && tmp != map->end)
			{
				if (is_dead_end_first(tmp) == 1)
				{
					*changed = 1;
					remove_dead_path(&tmp, map);
				}
			}
		}
		i++;
	}
}

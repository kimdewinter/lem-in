/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_remove_dead_ends.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 11:20:18 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/22 13:21:30 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int		is_dead_end_first(t_room *curr, t_map *map)
{
	size_t	i;
	size_t	mutual;

	mutual = 0;
	i = 0;
	printf("Curr %s conns to %lu\n", curr->name, curr->conns_to);
	if (curr->viable_nbs == 0 || curr->conns_to == 0)
		return (1);
	if (curr->viable_nbs == 1)
	{
		while (i < curr->neighbours_len)
		{
			if (room_in_bitfield(curr->neighbours[i], curr->unavailable) == 0)
			{
				/* If it can only go to one place and that is not end or
				connected to end, this is a dead end */
				printf("nb %s\n", curr->neighbours[i]->name);
				if (is_mutual_conn(curr, curr->neighbours[i]) == 1
				&& ((curr->conns_to > 1
				&& (curr->neighbours[i]->spe != 1
				&& curr->neighbours[i] != map->end))
				|| curr->conns_to == 1))
				{
					printf("Mutual\n");
					mutual++;
				}
			}
			i++;
		}
		if (mutual >= 1)
		{
			// printf("Dead end first %s\n", curr->name);
			return (1);
		}
	}
	// if (curr->conns_to == 1)
	// {
	// 	printf("Only one way to get to this node\n");
	// 	exit (0);
	// }
	return (0);
}

static int		is_dead_end_cont(t_room *curr)
{
	size_t	i;
	size_t	mutual;

	i = 0;
	mutual = 0;
	if (curr->viable_nbs > 2)
		return (0);
	if (curr->viable_nbs == 1)
	{
		if (curr->conns_to == 1)
			return (1);
		if (curr->conns_to == 2)
		{
			while (i < curr->neighbours_len)
			{
				if (room_in_bitfield(curr->neighbours[i], curr->unavailable) == 0)
				{
					if (is_mutual_conn(curr, curr->neighbours[i]) == 1)
						mutual++;
				}
				i++;
			}
			if (mutual >= 1)
				return (1);
		}
	}
	else if (curr->viable_nbs == 2)
	{
		if (curr->conns_to == 1)
			return (1);
		if (curr->conns_to == 2)
		{
			while (i < curr->neighbours_len)
			{
				if (room_in_bitfield(curr->neighbours[i], curr->unavailable) == 0)
				{
					if (is_mutual_conn(curr, curr->neighbours[i]) == 1)
						mutual++;
				}
				i++;
			}
			if (mutual >= 2)
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
	// printf("DEAD %s\nnbs %lu\n", dead->name, dead->neighbours_len);
	while (i < dead->neighbours_len)
	{
		// printf("Neighbour: %s\n", dead->neighbours[i]->name);
		if (dead->neighbours[i] != NULL)
		{
			j = 0;
			nb = dead->neighbours[i];
			while (j < nb->neighbours_len)
			{
				if (nb->neighbours[j] == dead)
				{
					//j -= 
					// handle_nowhere_to_go(nb, dead, map);
					i -= handle_nowhere_to_go(dead, nb, map);
					// printf("j %lu\n", j);
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
	// printf("prev %s\n", prev->name);
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
				if (is_dead_end_first(tmp, map) == 1)
				{
					*changed = 1;
					printf("Dead end first %s viable nbs %lu conns to %lu\n", tmp->name,
					tmp->viable_nbs, tmp->conns_to);
					remove_dead_path(&tmp, map);
				}
			}
		}
		i++;
	}
}

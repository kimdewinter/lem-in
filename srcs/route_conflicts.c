/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_conflicts.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 13:21:10 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/07 13:59:27 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int			is_junction(t_room *dst, size_t round)
{
	size_t	i;
	int		viable;

	i = 0;
	if (dst->num_options != 0)
	{
		dst->checked = 1;
		return (1);
	}
	viable = 0;
	dst->checked = 1;
	while (i < dst->neighbours_len)
	{
		if (dst->neighbours[i]->dead_end == 0
		&& (dst->neighbours[i]->weight == 0
		|| dst->neighbours[i]->weight > dst->weight 
		|| (dst->neighbours[i]->weight < dst->weight &&
		dst->weight > round)))
		{
			viable++;
			if (viable > 1)
				return (1);
		}
		i++;
	}
	return (0);
}

static void			solve_path_conflict(t_queue *item, t_subpath *new,
size_t j, int *add)
{
	if (new->sp == 1)
	{
		if (new->segment_len == item->dst->routes[j]->segment_len)
		{
			if (new->segment_len == 0)
				return ;
			else if (new->segment_len != 0)
			{
				if (new->path[new->start + 1] ==
				item->dst->routes[j]->path[item->dst->routes[j]->start + 1])
					return ;
			}
			*add = 0;
		}
		else if (new->segment_len < item->dst->routes[j]->segment_len)
		{
			free (item->dst->routes[j]);
			item->dst->routes[j] = new;
		}
		else
		{
			free (new);
			new = NULL;
		}
		*add = 0;	
	}
}

void			solve_conflict(t_queue *item,
t_subpath *new, int *add)
{
	ssize_t	j;

	j = item->dst->num_options - 1;
	while (j >= 0 && item->dst->routes[j]->added_this_turn == 1)
	{
		if (item->dst->routes[j]->conj == new->conj)
		{
			solve_path_conflict(item, new, j, add);
			return ;
		}
		j--;
	}
}

void			solve_spe_conflict(t_queue *item, t_subpath *new,
t_map *map, int *add)
{
	ssize_t	j;

	j = item->dst->num_options - 1;
	while (j >= 0)
	{
		if (item->dst->routes[j]->conj == map->end)
		{
			if (new->len < item->dst->routes[j]->len)
			{
				// if (item->dst->routes[j])
				// 	free (item->dst->routes[j]);
				// item->dst->routes[j] = new;
				// *add = 0;
				return;
			}
			else
			{
				if (new)
					free (new);
				new = NULL;
				*add = 0;
				return ;
			}
		}
		j--;
	}
}
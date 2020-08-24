/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_tube.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/23 20:13:39 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/24 17:00:59 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int				is_junction(t_room *curr, t_map *map)
{
	if (curr == map->start || curr == map->end || curr->neighbours_len > 2)
		return (1);
	return (0);
}

static void		check_junction(t_room *from, t_room *to, t_map *map)
{
	if (is_junction(to, map) == 0)
		to->is_junction = 0;
	if (is_junction(from, map) == 0)
		from->is_junction = 0;
}

static int		rearrange_nbs(t_room *from, size_t i)
{
	t_room *tmp;

	tmp = NULL;
	if (from->neighbours_len == 1)
	{
		from->neighbours[i] = NULL;
		return (0);
	}
	else
	{
		tmp = from->neighbours[from->neighbours_len - 1];
		from->neighbours[from->neighbours_len - 1] = NULL;
		from->neighbours[i] = tmp;
		return (1);
	}
}

void			del_tube(t_room *from, t_room *to, t_map *map)
{
	int		found;
	size_t	i;

	i = 0;
	found = 0;
	while (i < from->neighbours_len && found == 0)
	{
		if (from->neighbours[i] == to)
		{
			rearrange_nbs(from, i);
			found = 1;
		}
		i++;
	}
	if (found == 1)
	{
		from->neighbours_len--;
		check_junction(from, to, map);
	}
}

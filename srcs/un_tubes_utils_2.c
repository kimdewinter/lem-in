/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_tubes_utils_2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 11:48:42 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/17 11:48:58 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int				is_junction(t_room *curr, t_map *map)
{
	size_t	mutual;
	size_t	i;

	mutual = 0;
	i = 0;
	if (curr == map->start || curr == map->end)
		return (1);
	if (curr->viable_nbs == 1 && curr->conns_to == 1)
		return (0);
	if (curr->viable_nbs == 2)
	{
		if (curr->conns_to == 1)
		{
			while (i < curr->neighbours_len)
			{
				if (room_in_bitfield(curr->neighbours[i], curr->unavailable) == 0
				&& is_mutual_conn(curr, curr->neighbours[i]) == 1)
					mutual++;
				i++;
			}
			if (mutual >= 1)
				return (0);
		}
		else if (curr->conns_to == 2)
		{
			while (i < curr->neighbours_len)
			{
				if (room_in_bitfield(curr->neighbours[i], curr->unavailable) == 0
				&& is_mutual_conn(curr, curr->neighbours[i]) == 1)
					mutual++;
				i++;
			}
			if (mutual >= 2)
				return (0);
		}
	}
	return (1);
}

static void		check_junction(t_room *from, t_room *to, t_map *map, int found)
{
	if (found == 1)
	{
		to->conns_to--;
		from->viable_nbs--;
		if (is_junction(to, map) == 0)
			to->is_junction = 0;
		if (is_junction(from, map) == 0)
			from->is_junction = 0;
	}
}

static int		rearrange_nbs(t_room *from, t_room *to, size_t i)
{
	t_room *tmp;

	tmp = NULL;
	bite_add_room_to_bitfield(to, from->removed_conns);
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

void			set_unavailable(t_room *from, t_room *to, int *changed,
t_map *map)
{
	if (room_in_bitfield(to, from->unavailable) == 1)
		return ;
	*changed = 1;
	if (room_in_bitfield(from, to->unavailable) == 1)
	{
		del_tube(from, to, map);
		del_tube(to, from, map);
	}
	else
	{
		bite_add_room_to_bitfield(to, from->removed_conns);
		bite_add_room_to_bitfield(to, from->unavailable);
		check_junction(from, to, map, 1);
	}
}

int				del_tube(t_room *from, t_room *to, t_map *map)
{
	int		found;
	int		ret;
	size_t	i;

	i = 0;
	found = 0;
	ret = 0;
	while (i < from->neighbours_len && found == 0)
	{
		if (from->neighbours[i] == to)
		{
			if (room_in_bitfield(to, from->unavailable) == 1)
			{
				to->conns_to++;
				from->viable_nbs++;
			}
			ret = rearrange_nbs(from, to, i);
			found = 1;
		}
		i++;
	}
	if (found == 1)
		from->neighbours_len--;
	check_junction(from, to, map, found);
	return (ret);
}

int				has_conn_to(t_room *curr, t_room *nb)
{
	size_t	i;

	i = 0;
	if (room_in_bitfield(nb, curr->unavailable) == 1
	|| room_in_bitfield(nb, curr->removed_conns) == 1)
		return (0);
	while (i < curr->neighbours_len)
	{
		if (curr->neighbours[i] == nb)
			return (1);
		i++;
	}
	return (0);
}

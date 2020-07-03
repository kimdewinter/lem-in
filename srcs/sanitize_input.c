/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sanitize_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 16:41:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/03 14:33:41 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void		remove_dead_path(t_room **tmp, t_map *map)
{
	t_room	*prev;
	size_t	j;

	(*tmp)->dead_end = 1;
	prev = *tmp;
	*tmp = *((*tmp)->neighbours);
	j = 0;
	while ((*tmp)->neighbours_len == 2 && *tmp != map->start
	&& *tmp != map->end)
	{
		j = 0;
		(*tmp)->dead_end = 1;
		if ((*tmp)->neighbours[j] == prev)
			j++;
		prev = *tmp;
		*tmp = (*tmp)->neighbours[j];
	}
	(*tmp)->viable_nbs--;
}

static void		remove_dead_ends(t_map *map)
{
	size_t	i;
	t_room	*tmp;

	i = 0;
	while (i < map->rooms->size)
	{
		if (map->rooms->entries[i] != NULL)
		{
			tmp = ((t_room *)map->rooms->entries[i]->val);
			if (tmp != map->start && tmp != map->end && tmp->dead_end == 0)
			{
				if (tmp->neighbours_len == 1)
					remove_dead_path(&tmp, map);
			}
		}
		i++;
	}
}

static void		flag_conj(t_map *map)
{
	size_t	i;
	t_room	*tmp;

	i = 0;
	while (i < map->rooms->size)
	{
		if (map->rooms->entries[i] != NULL)
		{
			tmp = ((t_room *)map->rooms->entries[i]->val);
			if (tmp->viable_nbs > 2 || (tmp->viable_nbs >= 2 &&
			(tmp == map->start || tmp == map->end)))
				tmp->is_conj = 1;
		}
		i++;
	}
}

static int			check_connections(t_room *curr)
{
	size_t	i;
	size_t	connections;

	i = 0;
	connections = 0;
	while (i < curr->neighbours_len)
	{
		if (curr->neighbours[i]->dead_end == 0)
		{
			connections++;
			break;
		}
		i++;
	}
	if (connections == 0)
		return (0);
	return (1);
}

size_t			sanitize_input(t_map *map)
{
	t_room *tmp;

	if (map->rooms == NULL)
		return (parse_error(8));
	if (map->start == NULL)
		return (parse_error(9));
	if (map->end == NULL)
		return (parse_error(10));
	tmp = (t_room *)search_ht(map->rooms, map->start->name);
	if (tmp->neighbours == NULL)
		return (parse_error(11));
	tmp = (t_room *)search_ht(map->rooms, map->end->name);
	if (tmp->neighbours == NULL)
		return (parse_error(12));
	remove_dead_ends(map);
	flag_conj(map);
	if (check_connections(map->start) == 0 ||
	check_connections(map->end) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

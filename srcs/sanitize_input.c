/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sanitize_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 16:41:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/17 21:29:02 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int					is_mutual_conn(t_room *curr, t_room *nb)
{
	size_t	i;

	i = 0;
	while (i < nb->neighbours_len)
	{
		if (nb->neighbours[i] == curr)
			return (1);
		i++;
	}
	return (0);
}

static void			flag_conj(t_map *map)
{
	size_t	i;
	t_room	*tmp;

	i = 0;
	while (i < map->rooms->size)
	{
		if (map->rooms->entries[i] != NULL)
		{
			tmp = ((t_room *)map->rooms->entries[i]->val);
			if (is_junction(tmp, map) == 1)
				tmp->is_junction = 1;
		}
		i++;
	}
}

static ssize_t		regular_checks(t_map *map)
{
	t_room	*tmp;

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
	return (1);
}

ssize_t				sanitize_input(t_map *map)
{
	int		changed;
	size_t	res;

	changed = 1;
	res = regular_checks(map);
	if (res != 1)
		return (res);
	flag_conj(map);
	remove_sps_spe_conns(map);
	while (changed > 0)
	{
		changed = 0;
		set_weights(map, -1);
		remove_dead_ends(map, &changed);
		if (map->start->neighbours_len == 0 ||
			map->end->neighbours_len == 0)
			return (EXIT_FAILURE);
		flag_conj(map);
		remove_unnecessary_tubes(map, &changed);
		flag_conj(map);
	}
	if (map->start->neighbours_len == 0 || map->end->neighbours_len == 0)
		return (EXIT_FAILURE);
	// print_map(map);
	exit (0);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sanitize_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 16:41:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/23 20:37:11 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

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

ssize_t				sanitize_input(t_map *map)
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
	flag_conj(map);
	set_spe_rooms(map);
	return (EXIT_SUCCESS);
}

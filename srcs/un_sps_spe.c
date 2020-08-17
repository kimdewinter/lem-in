/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_sps_spe.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 11:16:45 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/17 11:23:19 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void		remove_sps_conns(t_room *src, t_map *map)
{
	size_t	j;

	j = 0;
	while (j < src->neighbours_len)
	{
		if (src->neighbours[j] != NULL
		&& src->neighbours[j]->sps == 1
		&& src->neighbours[j] != map->start)
			j -= del_tube(src, src->neighbours[j], map);
		j++;
	}
}

static void		remove_spe_conns(t_room *src, t_map *map)
{
	size_t	j;

	j = 0;
	while (j < src->neighbours_len)
	{
		if (src->neighbours[j] != NULL
		&& src->neighbours[j]->spe == 1
		&& src->neighbours[j] != map->end)
			j -= del_tube(src, src->neighbours[j], map);
		j++;
	}
}

void			remove_sps_spe_conns(t_map *map)
{
	size_t	i;
	t_room	*tmp;

	i = 0;
	while (i < map->rooms->size)
	{
		if (((t_entry *)map->rooms->entries[i]) != NULL)
		{
			tmp = ((t_room *)map->rooms->entries[i]->val);
			if (tmp->sps == 1 && tmp != map->start)
				remove_sps_conns(tmp, map);
			if (tmp->spe == 1 && tmp != map->end)
				remove_spe_conns(tmp, map);
		}
		i++;
	}
}

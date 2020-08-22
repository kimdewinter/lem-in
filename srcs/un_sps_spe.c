/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_sps_spe.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 11:16:45 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/20 21:03:34 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

// static void		remove_sps_conns(t_room *src, t_map *map)
// {
// 	size_t			j;
// 	t_connection	tmp;

// 	j = 0;
// 	setup_conn(&tmp, src);
// 	while (j < src->neighbours_len)
// 	{
// 		setup_conn(&tmp, src);
// 		set_conn(&tmp, src->neighbours[j]);
// 		// if (src->neighbours[j] != NULL
// 		// && src->neighbours[j]->sps == 1
// 		// && src->neighbours[j] != map->start)
// 		if (tmp.dst != NULL
// 		&& tmp.dst->sps == 1
// 		&& tmp.dst != map->start)
// 			j -= remove_path(&tmp, map);//del_tube(src, src->neighbours[j], map);
// 		j++;
// 	}
// }

// static void		remove_spe_conns(t_room *src, t_map *map)
// {
// 	size_t			j;
// 	t_connection	tmp;

// 	j = 0;
// 	setup_conn(&tmp, src);
// 	while (j < src->neighbours_len)
// 	{
// 		setup_conn(&tmp, src);
// 		set_conn(&tmp, src->neighbours[j]);
// 		// if (src->neighbours[j] != NULL
// 		// && src->neighbours[j]->spe == 1
// 		// && src->neighbours[j] != map->end)
// 		if (tmp.dst != NULL
// 		&& tmp.dst->spe == 1
// 		&& tmp.dst != map->end)
// 			j -= remove_path(&tmp, map);//del_tube(src, src->neighbours[j], map);
// 		j++;
// 	}
// }

t_room			*find_last(t_room *start, int dir)
{
	t_room	*curr;
	size_t	i;

	curr = start;
	i = 0;
	while (curr->is_junction == 0)
	{
		i = 0;
		while (i < curr->neighbours_len)
		{
			if (dir == 1)
			{
				if (curr->neighbours[i]->dist_to_start > curr->dist_to_start)
				{
					curr = curr->neighbours[i];
					break ;
				}
			}
			else
			{
				if (curr->neighbours[i]->dist_to_end > curr->dist_to_end)
				{
					curr = curr->neighbours[i];
					break ;
				}
			}
			i++;
		}
	}
	return (curr);
}

void			remove_sps_spe_conns(t_map *map)
{
	size_t			i;
	t_connection	tmp;
	// t_room			*tmp;

	i = 0;
	setup_conn(&tmp, map->start);
	while (i < map->start->neighbours_len)
	{
		setup_conn(&tmp, map->start);
		set_conn(&tmp, map->start->neighbours[i]);
		// print_connection(&tmp);
		// tmp = find_last(map->start->neighbours[i], 1);
		// printf("FOUND %s\n", tmp->name);
		i++;
	}
	// while (i < map->rooms->size)
	// {
	// 	if (((t_entry *)map->rooms->entries[i]) != NULL)
	// 	{
	// 		tmp = ((t_room *)map->rooms->entries[i]->val);
	// 		if (tmp->sps == 1 && tmp != map->start)
	// 			remove_sps_conns(tmp, map);
	// 		if (tmp->spe == 1 && tmp != map->end)
	// 			remove_spe_conns(tmp, map);
	// 	}
	// 	i++;
	// }
}

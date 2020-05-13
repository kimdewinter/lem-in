/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/08 15:11:52 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/13 15:39:10 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void	debug(t_map *map)
{
	t_table *table;
	t_room *tmp;

	table = map->rooms;
	ft_printf("\nPRINT MAP\n\n");
	if (map->start)
		ft_printf("START: %s\n", map->start);
	if (map->end)
		ft_printf("END: %s\n", map->end);
	for (int i = 0; i < table->size; i++)
	{
		if (table->entries[i] != NULL)
		{
			ft_printf("KEY: %s\n", table->entries[i]->key);
			tmp = (t_room *)table->entries[i]->val;
			for (size_t j = 0; j < tmp->neighbours_len; j++)
				ft_printf("NEIGHBOUR: %d %s\n", j, tmp->neighbours[j]->name);
		}
	}
}

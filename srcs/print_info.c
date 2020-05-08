/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_info.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/08 15:11:52 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/08 15:15:08 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	debug(t_map *map)
{
	t_table *table;
	char *tmp;

	table = map->rooms;
	ft_printf("\nPRINT MAP\n\n");
	ft_printf("NUMBER OF ROOMS: %d\nNUMBER OF LINKS: %d\n",
	map->rooms_amnt, map->links_amnt);
	if (map->start)
		ft_printf("START: %s\n", map->start);
	if (map->end)
		ft_printf("END: %s\n", map->end);
	for (int i = 0; i < table->size; i++)
	{
		if (table->entries[i] != NULL)
		{
			ft_printf("KEY: %s\n", table->entries[i]->key);
		}
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/08 15:11:52 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/25 13:27:52 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void	print_routes(t_map *map)
{
	t_route **tmp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	tmp = map->routes;
	printf("NUM ROUTES %lu\n", map->num_routes);
	while (i < map->num_routes)
	{
		printf("ROUTE %ld DEAD %d SOLVED %d\nLEN %lu\n", i, tmp[i]->dead, tmp[i]->solved, tmp[i]->len);
		j = 0;
		while (j < tmp[i]->len)
		{
			printf("%s ", tmp[i]->route[j]->name);
			j++;
		}
		printf("\n\n");
		i++;
	}
}

void	print_bitroom(t_map *map, t_room *room)
{
	size_t	i;

	i = 0;
	while (i < map->bitfield_len)
	{
		printf("%lu\n", room->bitroom[i]);
		i++;
	}
}

void	print_bitroute(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->num_routes)
	{
		j = 0;
		while (j < map->bitfield_len)
		{
			printf("%lu\n", map->routes[i]->bitroute[j]);
			j++;
		}
		i++;
	}
	
}

void	debug(t_map *map)
{
	t_table *table;
	t_room *tmp;

	table = map->rooms;
	ft_printf("\nPRINT MAP\n\n");
	if (map->start)
		ft_printf("START: %s\n", map->start->name);
	if (map->end)
		ft_printf("END: %s\n", map->end->name);
	for (int i = 0; i < table->size; i++)
	{
		if (table->entries[i] != NULL)
		{
			ft_printf("KEY: %s\n", table->entries[i]->key);
			tmp = (t_room *)table->entries[i]->val;
			printf("ID: %lu\n", tmp->room_i);
			for (size_t j = 0; j < tmp->neighbours_len; j++)
				ft_printf("NEIGHBOUR: %d %s\n", j, tmp->neighbours[j]->name);
		}
	}
}

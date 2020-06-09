/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/08 15:11:52 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/09 13:42:54 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

// void	print_bitroom(t_map *map, t_room *room)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < map->bitfield_len)
// 	{
// 		printf("%lu\n", room->bitroom[i]);
// 		i++;
// 	}
// }
void	print_bitconj(uint64_t *arr, size_t len)
{
	size_t	i;

	i = 0;
	printf("Bitconj\n");
	while (i < len)
	{
		printf("%lu \n", arr[i]);
		i++;
	}

}

void	print_troute(t_routes_wrapper *wroutes)
{
	size_t	i;
	size_t	j;

	i = 0;
	printf("Number of routes %lu\n", wroutes->num_paths);
	while (i < wroutes->num_paths)
	{
		j = 0;
		printf("Route:\n");
		printf("Len %lu\nEnd: %d\nConj %s\nAnts %lu\n", wroutes->routes[i]->len, wroutes->routes[i]->end,
		wroutes->routes[i]->last_conj->name, wroutes->routes[i]->ants);
		print_bitconj(wroutes->routes[i]->bitroute, 1);
		while (j < wroutes->routes[i]->len)
		{
			printf("%s ", wroutes->routes[i]->route[j]->name);
			j++;
		}
		printf("\n\n");
		i++;
	}
}

void	print_path(t_subpath *pt)
{
	size_t	i;
	
	i = 0;
	if (!pt)
		return;
	printf("Len path %ld\n", pt->len);
	while (i < pt->len)
	{
		printf("%s ", pt->path[i]->name);
		i++;
	}
	printf("\n\n");
}

void	print_queue(t_list **queue)
{
	t_list *item;
	t_subpath *pt;
	t_room *dst;
	t_room *src;

	ft_printf("\nPRINT QUEUE\n\n");
	item = *queue;
	while (item)
	{
		printf("Item %p %p path %p dst %p\n", item, (t_queue *)item->content,
		((t_queue *)item->content)->dst, ((t_queue *)item->content)->path);
		dst = ((t_queue *)item->content)->dst;
		src = ((t_queue *)item->content)->src;
		pt = ((t_queue *)item->content)->path;
		printf("Destination: %s spe %d sps %d\nSource: %s spe %d sps %d\n",
		dst->name, dst->spe, dst->sps, src->name, src->spe, src->sps);
		print_path(pt);
		item = item->next;
	}
}

void	print_paths(t_room *room)
{
	for (size_t i = 0; i < room->num_options; i++)
	{
		printf("CONJ: %s\nOPTIONS: %lu\nLEN: %lu\n", room->routes[i]->conj->name, 
		room->num_options, room->routes[i]->len);
		for (size_t j = 0; j < room->routes[i]->len; j++)
		{
			if (room->routes[i]->path[j] != NULL)
				printf("%s ", room->routes[i]->path[j]->name);
		}
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
				ft_printf("NEIGHBOUR: ID %d KEY %s\n", j, tmp->neighbours[j]->name);
			print_paths(tmp);
			printf("\n\n");
		}
	}
}

void	print_route_rooms(const t_route *rte, const size_t *rte_index)
{
	size_t	i;

	i = 0;
	if (rte_index != NULL)
		ft_printf("\nROUTE'S INDEX: %i\n", *rte_index);
	while (i < rte->len)
	{
		ft_printf("%s ", rte->route[i]->name);
		i++;
	}
	ft_printf("\n");
}

void	print_n_routes(const t_route **rtes, const size_t n)
{
	size_t	i;

	i = 0;
	ft_printf("PRINTING ROUTE-COMBINATION:\n");
	while (i < n)
	{
		print_route_rooms(rtes[i], NULL);
		i++;
	}
}

void		print_solution(t_map *map)
{
	size_t	i;

	i = 0;
	printf("SOLUTION\nrounds: %lu\n", map->solution.turns);
	while (i < map->solution.used)
	{
		printf("%lu\n", map->solution.combi[i]->ants);
		print_route_rooms(map->solution.combi[i], NULL);
		i++;
	}
}
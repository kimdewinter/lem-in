/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/08 15:11:52 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/21 09:53:16 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

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
void		print_routes(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < map->num_routes)
	{
		j = 0;
		printf("\n\nPath:\n");
		// print_bitconj(map->routes[i]->bitroute, map->bitfield_len);
		while (j < map->routes[i]->len)
		{
			printf("%s ", map->routes[i]->route[j]->name);
			j++;
		}
		printf("\n");
		i++;
	}
}

static void	print_names(char **names, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		ft_printf("%s ", names[i]);
		i++;
	}
	printf("\n");
}

static void	print_ants(size_t *ants, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		ft_printf("%lu ", ants[i]);
		i++;
	}
	printf("\n");
}

void		print_routeput(t_routeput **routes, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		print_names(routes[i]->rooms, routes[i]->rooms_len);
		print_ants(routes[i]->ants, routes[i]->rooms_len);
		i++;
	}
}

void		print_bitconj(uint64_t *arr, size_t len)
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

void		print_troute(t_routes_wrapper *wroutes)
{
	size_t	i;
	size_t	j;

	i = 0;
	printf("Number of routes %lu\n", wroutes->num_paths);
	while (i < wroutes->num_paths)
	{
		j = 0;
		printf("Route:\n");
		printf("Len %lu\nEnd: %d\nConj %s\nAnts %lu\n", wroutes->routes[i]->len,
			wroutes->routes[i]->end, wroutes->routes[i]->last_conj->name,
			wroutes->routes[i]->ants);
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
	t_subpath *tmp;
	
	if (pt == NULL)
		return;
	i = pt->start + 1;
	printf("Len path %ld\nAdded this turn %d\nSP %d\n", pt->len, pt->added_this_turn, pt->sp);
	printf("conj %s\n", pt->conj->name);
	while (i < pt->segment_len + pt->start + 1)
	{
		if (pt->path[i] != NULL)
			printf("%s ", pt->path[i]->name);
		i++;
	}
	tmp = pt->next;
	// if (pt->conj->name[0] == '4')
	// {
	// 	printf("next %p next %p\n", tmp, tmp->next);
	// 	// exit (0);
	// }
	while (tmp != NULL)
	{
		printf("conj %s\n", tmp->conj->name);
		for (size_t j = tmp->start + 1; j < tmp->size; j++)
		{
			if (tmp->path[j] != NULL)
				printf("%s ", tmp->path[j]->name);
		}
		tmp = tmp->next;
		// printf("tmp %p\n", tmp);
	}
	printf("\n\n");
}

void	print_queue(t_qwrap *qr)
{
	t_subpath *pt;
	t_room *dst;
	t_room *src;
	t_queue	*q;

	printf("Items: %lu\n", qr->items);
	q = *(qr->queue);
	while (q)
	{
		printf("ITEM\n\n");
		dst = q->dst;
		src = q->src;
		pt = q->path;
		printf("dst: %s\nsrc %s\ndst weight %lu\nsrc weight %lu\n", dst->name, src->name, dst->weight, src->weight);
		if (pt)
		{
			print_path(pt);
		}
		// printf("Dst paths\n");
		// print_paths(dst);
		// else
		// {
		// 	printf("No entry %ld\n", i);
		// }
		q = q->next;
	}
	// ft_printf("\nPRINT QUEUE\n\n");
	// i = 0;
	// while (item)
	// {
	// 	printf("new conj %d\n", ((t_queue *)item->content)->new_conj);
	// 	dst = ((t_queue *)item->content)->dst;
	// 	src = ((t_queue *)item->content)->src;
	// 	pt = ((t_queue *)item->content)->path;
	// 	// added_path = ((t_queue *)item->content)->added_path;
	// 	printf("Destination: %s spe %d sps %d\nSource: %s spe %d sps %d\n",
	// 	dst->name, dst->spe, dst->sps, src->name, src->spe, src->sps);
	// 	print_path(pt);
	// 	// printf("Added path:\n");
	// 	// if (added_path)
	// 	// 	print_path(added_path);
	// 	item = item->next;
	// }
}

void	print_paths(t_room *room)
{
	t_subpath	*tmp;

	printf("\nPaths: %lu\n", room->num_options);
	for (size_t i = 0; i < room->num_options; i++)
	{
		if (room->routes[i] != NULL)
		{
			printf("\nSP: %u\nCONJ: %s\nLen %lu\nSeg len %lu\n",room->routes[i]->sp, room->routes[i]->conj->name,
			room->routes[i]->len, room->routes[i]->segment_len);
			for (size_t j = room->routes[i]->start + 1; j < room->routes[i]->size; j++)
			{
				if (room->routes[i]->path[j] != NULL)
					printf("%s ", room->routes[i]->path[j]->name);
			}
			tmp = room->routes[i]->next;
			printf("\n");
			while (tmp)
			{
				printf("CONJ %s\n", tmp->conj->name);
				for (size_t j = tmp->start + 1; j < tmp->size; j++)
				{
					if (tmp->path[j] != NULL)
						printf("%s ", tmp->path[j]->name);
				}
				tmp = tmp->next;
			}
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
	for (size_t i = 0; i < table->size; i++)
	{
		if (table->entries[i] != NULL)
		{
			ft_printf("KEY: %s\nIS CONJ %d\nVIABLE NBS: %d\nWEIGHT %lu\nSPE %d\n%lu\n", table->entries[i]->key, 
			((t_room *)table->entries[i]->val)->is_conj, ((t_room *)table->entries[i]->val)->viable_nbs,
			((t_room *)table->entries[i]->val)->weight, ((t_room *)table->entries[i]->val)->spe,
			((t_room *)table->entries[i]->val)->start_dst);
			tmp = (t_room *)table->entries[i]->val;
			printf("bitconj\n");
			print_bitconj(tmp->bitconj, map->bitfield_len);
			printf("ID: %lu\nDead end: %d\n", tmp->room_i, tmp->dead_end);
			for (size_t j = 0; j < tmp->neighbours_len; j++)
				ft_printf("NEIGHBOUR: ID %d KEY %s\n", j, tmp->neighbours[j]->name);
			print_paths(tmp);
			printf("\n\n");
		}
	}
}

void		print_route_rooms(const t_route *rte, const size_t *rte_index)
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

void		print_n_routes(const t_route **rtes, const size_t n)
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

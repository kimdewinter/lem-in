/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 14:33:23 by kim           #+#    #+#                 */
/*   Updated: 2020/07/01 13:27:54 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t			increase_routes_size(t_room **dst, t_map *map)
{
	size_t		i;
	size_t		new_size;
	t_subpath	**new_routes;

	i = 0;
	if ((*dst)->routes_size == 0)
	{
		new_size = (map->rooms->count * 100) / ((100 / INIT_ROUTE_PERC) * 100);
		if (new_size == 0)
			new_size = map->rooms->count;
	}
	else
		new_size = (*dst)->routes_size * 2;
	new_routes = (t_subpath **)malloc(sizeof(t_subpath *) * new_size);
	if (new_routes)
	{
		while (i < (*dst)->routes_size)
		{
			new_routes[i] = (*dst)->routes[i];
			i++;
		}
		if ((*dst)->routes)
			free ((*dst)->routes);
		(*dst)->routes = new_routes;
		(*dst)->routes_size = new_size;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static size_t		create_new_path(t_subpath **new, t_subpath *pt, t_room *conj, 
t_map *map)
{
	new_subpath(new, conj, map);
	if (*new)
	{
		(*new)->len += 1;
		if (pt)
		{
			(*new)->len += pt->len;
			(*new)->sp = pt->sp;
		}
		(*new)->next = pt;
		if (pt != NULL)
		{
			if (bite_bitroute_copy((*new)->bitconj, pt->bitconj, map) == EXIT_FAILURE)
			{
				free (*new);
				return (EXIT_FAILURE);
			}
		}
		add_conj_to_bitroute(conj, (*new)->bitconj);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

size_t			increase_route_size(t_subpath **pt, t_map *map)
{
	t_subpath	*tmp;
	size_t		new_size;
	t_room		**new_route;
	size_t		i;
	ssize_t		j;

	tmp = *pt;
	if (tmp->size == 0)
	{
		new_size = (map->rooms->count * 100) / ((100 / INIT_ROUTE_PERC) * 100);
		if (new_size == 0)
			new_size = map->rooms->count;
	}
	else
		new_size = tmp->size * 2;
	i = new_size - 1;
	j = (*pt)->size - 1;
	new_route = new_path(new_size);
	if (new_route)
	{
		while (j >= 0)
		{
			new_route[i] = tmp->path[j];
			j--;
			i--;
		}
		free ((*pt)->path);
		(*pt)->path = new_route;
		(*pt)->size = new_size;
		(*pt)->start = i;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

size_t		add_to_path(t_subpath *pt, t_room *add, t_map *map)
{
	if (pt->start < 0)
	{
		if (increase_route_size(&pt, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	pt->path[pt->start] = add;
	pt->start -= 1;
	pt->len += 1;
	pt->segment_len += 1;
	return (EXIT_SUCCESS);
}

size_t				add_nodes_to_path(t_queue *item, t_subpath **path,
t_map *map, int *add)
{
	t_room *nb;
	t_room *prev;
	size_t	i;
	int		found;

	prev = NULL;
	nb = item->dst;
	if (nb->weight == 0 && nb != map->start)
		nb->weight = item->dst->weight;
	while (nb->is_conj == 0 && nb != map->start)
	{
		i = 0;
		found = 0;
		while (i < nb->neighbours_len)
		{
			if (nb->neighbours[i]->nb->dead_end == 0
			&& nb->neighbours[i]->nb != prev
			&& nb->neighbours[i]->nb != (*path)->conj
			&& nb->neighbours[i]->nb != map->end)
			{
				found = 1;
				printf("NB FOUND %s\n", nb->name);
				if (nb->is_conj == 0)
				{
					if (add_to_path(*path, nb, map) == EXIT_FAILURE)
						return (EXIT_FAILURE);
					nb->dead_end = 1;
				}
				prev = nb;
				if (prev)
					printf("Prev %s\n", prev->name);
				nb = nb->neighbours[i]->nb;
				if (nb != map->start && nb->weight == 0)
					nb->weight = prev->weight + 1;
				printf("Weight %lu\n", nb->weight);
				printf("NB %s\n", nb->name);
				break;
			}
			i++;
		}
		if (found == 0)
			break;
	}
	if (found == 1)
	{
		printf("Prev weight %lu\n", prev->weight);
		if (nb != map->start && nb->weight == 0)
			nb->weight = prev->weight + 1;
		item->dst = nb;
	}
	else
		*add = 0;
	return (EXIT_SUCCESS);
}

static size_t				handle_path_src(t_subpath *path, t_queue *item,
t_map *map, t_subpath **new)
{
	printf("handle path src\n");
	if (item->src->is_conj == 0 && item->src != map->end)
	{
		if (add_to_path(path, item->src, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		path->sp = 1;
		item->src = path->conj;
		path->added_this_turn = 1;
		(*new) = path;
	}
	else
	{
		if (item->src != map->end)
		{
			if (create_new_path(new, path, item->src, map) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
		{
			(*new) = path;
			(*new)->added_this_turn = 1;
		}
	}
	print_path(*new);
	return (EXIT_SUCCESS);
}

static size_t				add_path_to_room(t_queue *item, t_map *map,
t_subpath **new)
{
	if (item->dst->routes_size <= item->dst->num_options)
	{
		if (increase_routes_size(&item->dst, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	item->dst->routes[item->dst->num_options] = *new;
	item->dst->num_options++;
	if (item->dst->weight == 0 && item->dst != map->start)
		item->dst->weight = item->src->weight + 1;
	add_bite_conj(item->dst, (*new)->conj);
	return (EXIT_SUCCESS);
}

static int			is_junction(t_queue *item, t_room *dst, t_map *map, size_t round)
{
	size_t	i;
	int		viable;

	i = 0;
	(void)map;
	(void)item;
	printf("Check if junction %s %lu\n", dst->name, dst->weight);
	if (dst->num_options != 0)
	{
		dst->checked = 1;
		return (1);
	}
	viable = 0;
	dst->checked = 1;
	printf("round %lu\n", round);
	while (i < dst->neighbours_len)
	{
		if (dst->neighbours[i]->nb->dead_end == 0
		&& dst->neighbours[i]->available == 1
		&& (dst->neighbours[i]->nb->weight == 0
		|| dst->neighbours[i]->nb->weight > dst->weight 
		|| (dst->neighbours[i]->nb->weight < dst->weight &&
		dst->weight > round)))
		{
			viable++;
			if (viable > 1)
			{
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static size_t		handle_path_dst(size_t round, t_queue *item, t_map *map,
t_subpath **new, int *add)
{
	if (item->dst != map->start && (item->dst->is_conj == 0 ||
	(item->dst->checked == 0 && is_junction(item, item->dst, map, round) == 0)))
	{
		item->dst->is_conj = 0;
		(*new)->sp = 1;
		if (add_nodes_to_path(item, new, map, add) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	print_path(*new);
	return (EXIT_SUCCESS);
}

static void			solve_conflict(t_room *dst, t_subpath *new, 
t_map *map, int *add)
{
	ssize_t	j;

	printf("solve conflict\n");
	j = dst->num_options - 1;
	while (j >= 0 && dst->routes[j]->added_this_turn == 1)
	{
		if (dst->routes[j]->conj == new->conj)
		{
			printf("old\n");
			print_path(dst->routes[j]);
			printf("new\n");
			print_path(new);
			if (new->segment_len < dst->routes[j]->segment_len)
			{
				free (dst->routes[j]);
				dst->routes[j] = new;
				*add = 0;
			}
			else
			{
				/* also free the rooms pointer */
				if (dst != map->start)
				{
					printf("removing path\n");
					free (new);
					*add = 0;
				}
			}
		}
		j--;
	}
	printf("%d\n", *add);
}

size_t				add_path(t_qwrap *qr, t_queue *item, t_subpath *path,
t_map *map)
{
	t_subpath	*new;
	int			add;

	new = NULL;
	add = 1;
	path->added_this_turn = 0;
	item->handled = 1;
	printf("DST: %s %lu\nSRC: %s %lu\n", item->dst->name, item->dst->weight,
	item->src->name, item->src->weight);
	if (handle_path_src(path, item, map, &new) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (handle_path_dst(qr->round, item, map, &new, &add) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (new->sp == 1 && has_path_to_conj(item->dst, new->conj) == 1)
	{
		solve_conflict(item->dst, new, map, &add);
	}
	if (add == 1)
	{
		printf("adding path\n");
		if (add_path_to_room(item, map, &new) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		item->path = new;
	}
	else
		item->path = NULL;
	// if (qr->round == 4 && item->src->name[0] == '5' && item->path->len == 5)
	// {
	// 	print_paths(map->start);
	// 	exit (0);
	// }
	return (EXIT_SUCCESS);
}

size_t				add_path_to_end(t_qwrap *qr, t_queue *item, t_map *map)
{
	t_subpath	*new;

	(void)item;
	if (create_new_path(&new, NULL, map->end, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (add_path(qr, item, new, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

size_t				add_path_to_dst(t_qwrap *qr, t_queue *curr, t_map *map)
{
	if (curr->src == map->end && qr->round == 1)
	{
		if (add_path_to_end(qr, curr, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		if (add_path(qr, curr, curr->path, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		printf("After add path\n");
		printf("DST: %s\nSRC %s\n\n\n", curr->dst->name, curr->src->name);
		print_path(curr->path);
	}
	return (EXIT_SUCCESS);
}

size_t			execute_queue(t_qwrap *qr, t_map *map)
{
	t_queue	*iter;

	iter = *(qr->queue);
	// printf("END IS JUNC %d\n", map->end->is_conj);
	// exit (0);
	while (iter)
	{
		if (add_path_to_dst(qr, iter, map) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		iter = iter->next;
		if (iter == NULL)
		{
			printf("\n\nBEFORE\n\n");
			print_queue(qr);
			printf("---------------------------\n");
			if (adjust_queue(qr, map) == EXIT_FAILURE)
			{
				return (EXIT_FAILURE);
			}
			iter = *(qr->queue);
			printf("\n\nAFTER\n\n");
			print_queue(qr);
			printf("---------------------------\n");
			// if (qr->round == 1)
			// 	exit (0);
		}
	}
	return (EXIT_SUCCESS);
}

size_t			find_routes(t_map *map)
{
	t_qwrap		*queue;

	// printf("before find routes\n");
	// setup_paths(map) == EXIT_SUCCESS &&
	// setup_paths(map) == EXIT_SUCCESS &&
	if (setup_queue(&queue, map) == EXIT_SUCCESS &&
		execute_queue(queue, map) == EXIT_SUCCESS)
	{
		// printf("%s\n", map->end->name);
		// printf("max parallels %lu", max_parallels(map));
		// print_paths(map->start);
		// debug (map);
		// print_paths(map->start);
		printf("Options: %lu\n", map->start->num_options);
		printf("\n\nSUCCESS\n\n");
		// print_paths(map->start);
		debug(map);
		exit (0);
		// build_paths(map);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
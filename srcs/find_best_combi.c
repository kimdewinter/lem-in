/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_best_combi.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 19:04:21 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/28 19:04:21 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t		setup_path_combi(size_t	num_paths, t_path_combi **new)
{
	(*new) = (t_path_combi *)malloc(sizeof(t_path_combi));
	if ((*new))
	{
		(*new)->has_options = 0;
		(*new)->compatible_paths = NULL;
		(*new)->cost = 0;
		(*new)->size = num_paths;
		(*new)->num_paths = 0;
		(*new)->index = 0;
		(*new)->search_index = 0;
		(*new)->next = NULL;
		(*new)->prev = NULL;
		(*new)->paths = (t_subpath	**)malloc(sizeof(t_subpath *) * num_paths);
		if ((*new)->paths)
			return (EXIT_SUCCESS);
		free ((*new));
	}
	return (EXIT_FAILURE);
}

static void		adjust_compatible_paths(t_path_combi *combi, int *new, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (new[i] == 0 && combi->compatible_paths[i] == 1)
		{
			combi->has_options--;
			combi->compatible_paths[i] = 0;
		}
		i++;
	}
}

static ssize_t	setup_compatible_combi(t_path_combi *combi, t_subpath *path,
t_map *map)
{
	size_t	i;

	i = 0;
	combi->has_options = path->max_compatible;
	combi->compatible_paths = (size_t *)malloc(sizeof(size_t) *
	map->start->num_options);
	if (combi->compatible_paths)
	{
		while (i < map->start->num_options)
		{
			combi->compatible_paths[i] = path->compatible_paths[i];
			i++;
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

ssize_t			add_to_combi(t_path_combi *combi, t_subpath *path, size_t ind, t_map *map)
{
	if (combi->index == 0)
	{
		if (setup_compatible_combi(combi, path, map) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
		adjust_compatible_paths(combi, path->compatible_paths,
		map->start->num_options);
	if (ind > combi->search_index)
		combi->search_index = ind;
	combi->paths[combi->index] = path;
	combi->index++;
	combi->num_paths++;
	return (EXIT_SUCCESS);
}

static void	commit_combi(t_path_combi **combis, t_path_combi *new, size_t ind)
{
	t_path_combi	*tmp;

	tmp = combis[ind];
	if (tmp == NULL)
		combis[ind] = new;
	else
	{
		new->next = tmp;
		tmp->prev = new;
		combis[ind] = new;
	}
}

static void		delete_combi(t_path_combi **combi)
{
	free ((*combi)->compatible_paths);
	(*combi)->compatible_paths = NULL;
	free ((*combi)->paths);
	(*combi)->paths = NULL;
	free ((*combi));
	*combi = NULL;
}

ssize_t		find_combis_of_two(t_path_combi **combis, t_map *map,
size_t	*active_combis)
{
	t_path_combi	*new;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	new = NULL;
	// printf("Find combis of 2\n");
	while (i < map->start->num_options)
	{
		// printf("orig i: %lu\n", i);
		j = i + 1;
		while (j < map->start->num_options)
		{
			if (map->start->routes[i]->compatible_paths[j] == 1)
			{
				// printf("Found \n");
				if (setup_path_combi(2, &new) == EXIT_FAILURE
				|| add_to_combi(new, map->start->routes[i], i, map) == EXIT_FAILURE)
					return (EXIT_FAILURE);
				if (add_to_combi(new, map->start->routes[j], j, map)
				== EXIT_FAILURE)
					return (EXIT_FAILURE);
				new->cost = calc_cost(map->antmount, new);
				/* If we commit, create a new one first !!*/
				if (new->cost < map->best->cost)
					map->best = new;
				if ((new->has_options != 0 &&
				((new->num_paths == map->best->num_paths
				&& new->has_options >= map->best->has_options))
				|| new->num_paths != map->best->num_paths) || map->best == new)
				{
					// printf("Commit\n");
					// printf("j: %lu\n", j);
					if (new->has_options != 0)
						(*active_combis)++;
					commit_combi(combis, new, 1);
				}
				else
					delete_combi(&new);
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

size_t		setup_best(t_path_combi **new, t_map *map)
{
	if (setup_path_combi(1, new) == EXIT_FAILURE
	|| add_to_combi(*new, map->shortest_path, 0, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	(*new)->cost = calc_cost(map->antmount, *new);
	return (EXIT_SUCCESS);
}

static ssize_t	setup_combis(t_path_combi ***combis, size_t max_combi)
{
	size_t	i;

	i = 0;
	(*combis) = (t_path_combi **)malloc(sizeof(t_path_combi *) * max_combi);
	if (!(*combis))
		return (EXIT_FAILURE);
	while (i < max_combi)
	{
		(*combis)[i] = NULL;
		i++;
	}
	return (EXIT_SUCCESS);
}

static void		merge_combi(t_subpath *new, t_path_combi *dst,
t_path_combi *src, t_map *map)
{
	size_t	i;

	i = 0;
	dst->has_options = src->has_options;
	while (i < map->start->num_options)
	{
		if (src->compatible_paths[i] == 1)
		{
			if (new->compatible_paths[i] == 0)
			{
				dst->compatible_paths[i] = 0;
				dst->has_options--;
			}
			else
				dst->compatible_paths[i] = 1;
		}
		i++;
	}
	while (dst->index < src->num_paths)
	{
		dst->paths[dst->index] = src->paths[dst->index];
		dst->index++;
	}
	dst->paths[dst->index] = new;
}

static ssize_t	find_combis_of_num(t_path_combi **combis, size_t num_to_combi,
t_map *map, size_t *active_combis)
{
	t_path_combi	*new;
	t_path_combi	*iter;
	size_t			i;
	size_t			j;
	size_t			k;

	i = 0;
	j = 0;
	k = 0;
	new = NULL;
	iter = combis[num_to_combi - 2];
	// printf("Find combis of %lu\n", num_to_combi);
	while (iter)
	{
		// printf("orig\n");
		/* Should be index of path already in combi with highest index ?? I think so */
		j = iter->search_index + 1;
		while (j < map->start->num_options)
		{
			if (iter->compatible_paths[j] == 1)
			{
				// printf("Found \n");
				if (setup_path_combi(num_to_combi, &new) == EXIT_FAILURE)
					return (EXIT_FAILURE);
				// merge_combi(map->start->routes[j], new, iter, map);
				// if (add_to_combi(new, map->sta
				k = 0;
				while (k < iter->num_paths)
				{
					if (add_to_combi(new, iter->paths[k], iter->search_index, map)
					== EXIT_FAILURE)
						return (EXIT_FAILURE);
					k++;
				}
				if (add_to_combi(new, map->start->routes[j], j, map)
				== EXIT_FAILURE)
					return (EXIT_FAILURE);
				new->cost = calc_cost(map->antmount, new);
				/* If we commit, create a new one first !!*/
				if (new->cost < map->best->cost)
					map->best = new;
				if ((new->has_options != 0
				&& new->has_options >= map->best->has_options) || map->best == new)
				{
					// printf("Commit\n");
					if (new->has_options != 0)
						(*active_combis)++;
					commit_combi(combis, new, num_to_combi - 1);
				}
				else
					delete_combi(&new);
			}
			j++;
		}
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}
/* combis contains all combinations of 1 in index 1, 2 in index 2 etc */
ssize_t		find_best_combi(t_map *map)
{
	t_path_combi	**combis;
	t_path_combi	*new_combi;
	size_t			max_combi;
	size_t			i;
	size_t			active_combis;

	max_combi = 0;
	active_combis = 0;
	if (setup_best(&new_combi, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	map->best = new_combi;
	max_parallels(&max_combi, map);
	if (setup_combis(&combis, max_combi) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	printf("Max parallels: %lu\n", max_combi);
	if (map->antmount == 1 || max_combi == 1 || map->shortest_path->len == 1)
		return (EXIT_SUCCESS);
	if (find_combis_of_two(combis, map, &active_combis) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// printf("COMBIS OF TWO\n");
	// print_combis(&(combis[1]));
	// exit (0);
	i = 2;
	while (i < max_combi && active_combis != 0)
	{
		// printf("In while\n");
		active_combis = 0;
		if (find_combis_of_num(combis, i + 1, map, &active_combis)
		== EXIT_FAILURE)
			return (EXIT_FAILURE);
		printf("COMBIS OF %lu\n", i + 1);
		// print_combis(&(combis[i]));
		i++;
		// exit(0);
		printf("Active combis %lu\n", active_combis);
		// if (i == 4)
		// 	exit (0);
	}
	printf("Number of paths %lu cost %lu\n", map->best->num_paths,
	map->best->cost);
	exit (0);
	print_combis(&(map->best));
	exit (0);
	return (EXIT_SUCCESS);
}
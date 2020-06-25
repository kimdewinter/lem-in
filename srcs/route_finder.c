/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 14:33:23 by kim           #+#    #+#                 */
/*   Updated: 2020/06/25 16:02:55 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t			add_path_to_nb(t_queue *curr)
{
	if (curr->new_conj == 1)
		return (add_new_conj_subpath(curr->dst, curr->src));
	else
		return (add_to_conj_path(curr->dst, curr->src, curr->path));
}

size_t			add_paths_to_start(t_map *map)
{
	size_t	i;
	size_t	added;

	i = 0;
	added = 0;
	while (i < map->start->neighbours_len)
	{
		if (map->start->neighbours[i]->num_options > 1)
		{
			if (!has_path_to_conj(map->start,
			map->start->neighbours[i]))
			{
				if (add_new_conj_subpath(map->start,
				map->start->neighbours[i]) == EXIT_FAILURE)
						return (EXIT_FAILURE);
				added++;
			}
		}
		else
		{
			if (map->start->neighbours[i]->num_options != 0 &&
			add_to_conj_path(map->start, map->start->neighbours[i],
			map->start->neighbours[i]->routes[0]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			added++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static void		init_values(size_t *len, t_list **iter, t_queue **curr,
t_qwrap *queue)
{
	*curr = NULL;
	*len = 0;
	(*iter) = (*queue->queue);
	if (*iter)
		(*curr) = (t_queue *)((*iter)->content);
}

static void		increase_values(size_t *len, t_list **iter, t_queue **curr)
{
	*curr = NULL;
	(*len)++;
	(*iter) = (*iter)->next;
	if (*iter)
		*curr = (t_queue *)((*iter)->content);
}

size_t			execute_queue(t_qwrap *queue, t_map *map)
{
	t_list	*iter;
	t_queue	*curr;
	size_t	len;

	init_values(&len, &iter, &curr, queue);
	while (iter)
	{
		if (add_path_to_nb(curr) == EXIT_FAILURE)
		{
			free_queue(&queue);
			return (EXIT_FAILURE);
		}
		increase_values(&len, &iter, &curr);
		if (iter == NULL)
		{
			if (adjust_queue(map, queue, len) == EXIT_FAILURE)
			{
				free_queue(&queue);
				return (EXIT_FAILURE);
			}
			init_values(&len, &iter, &curr, queue);
		}
	}
	free_queue(&queue);
	return (add_paths_to_start(map));
}

// ssize_t			check_dead_ends(t_map *map)
// {
// 	size_t	i;
// 	t_room	*prev;
// 	t_room	*tmp;
// 	size_t	j;
// 	size_t	dead_ends;

// 	j = 0;
// 	i = 0;
// 	dead_ends = 0;
// 	while (i < map->rooms->size)
// 	{
// 		if (map->rooms->entries[i] != NULL)
// 		{
// 			tmp = ((t_room *)map->rooms->entries[i]->val);
// 			if (tmp != map->start && tmp != map->end && tmp->dead_end == 0)
// 			{
// 				if (tmp->neighbours_len == 1)
// 				{
// 					tmp->dead_end = 1;
// 					dead_ends++;
// 					prev = tmp;
// 					tmp = (*tmp->neighbours)->nb;
// 					while (tmp->neighbours_len == 2 && tmp != map->start
// 					&& tmp != map->end)
// 					{
// 						j = 0;
// 						tmp->dead_end = 1;
// 						dead_ends++;
// 						if (tmp->neighbours[j]->nb == prev)
// 							j++;
// 						prev = tmp;
// 						tmp = tmp->neighbours[j]->nb;
// 					}
// 					tmp->viable_nbs--;
// 				}
// 			}
// 		}
// 		i++;
// 	}
// 	printf("Dead ends %lu\n", dead_ends);
// }

size_t			find_routes(t_map *map)
{
	t_qwrap		*queue;

	if (setup_paths(map) == EXIT_SUCCESS &&
		setup_queue(&queue, map) == EXIT_SUCCESS &&
		execute_queue(queue, map) == EXIT_SUCCESS &&
		build_paths(map) == EXIT_SUCCESS)
	{
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_setup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 13:45:50 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/20 11:07:05 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

#include "../includes/lemin.h"

static ssize_t				setup_room_adding(BITFIELD_TYPE **in_path,
t_map *map, t_subpath **path, t_room *nb)
{
	if (bite_alloc(in_path, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (add_to_path(*path, nb, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		is_not_junction(t_room *tmp, t_room *prev, t_map *map)
{
	if (prev == NULL)
	{
		if (tmp->is_conj == 0 && tmp != map->start)
			return (1);
		return (0);
	}
	if ((tmp->checked == 1 && tmp->is_conj == 0)
	|| (tmp->checked == 0 && is_junction(prev, tmp, map) == 0))
		return (1);
	return (0);
}

static int		is_viable_nb_setup(t_room *nb, t_room *prev,
t_map *map)
{
	if (nb != prev
	&& nb->dead_end == 0
	&& nb != map->end)
		return (1);
	return (0);
}

static void					set_if_found(t_room **tmp, t_room **dst,
t_room **prev, t_map *map)
{
	// if ((*tmp) != map->start && (*tmp)->weight == 0)
	// 	(*tmp)->weight = map->end->weight + 1;
	if ((*tmp) == map->end && prev)
		(*prev)->dead_end = 1;
	(*tmp)->spe = 1;
	*dst = *tmp;
}

static ssize_t				add_rooms_to_path(t_room **dst, t_room *nb,
t_subpath **path, t_map *map)
{
	t_room	*tmp;
	t_room	*prev;
	size_t	i;
	int		found;
	BITFIELD_TYPE	*in_path;

	prev = NULL;
	tmp = nb;
	*dst = NULL;
	(*path)->sp = 1;
	if (setup_room_adding(&in_path, map, path, nb) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	add_to_bitfield(tmp, in_path);
	while (is_not_junction(tmp, prev, map) == 1)
	{
		i = 0;
		found = 0;
		while (i < tmp->neighbours_len)
		{
			if (is_viable_nb_setup(tmp->neighbours[i], prev, map) == 1
			&& room_in_bitfield(tmp->neighbours[i], in_path) == 0)
			{
				if (is_not_junction(tmp->neighbours[i], prev, map) == 1)
				{
					if (add_to_path(*path, tmp->neighbours[i], map)
					== EXIT_FAILURE)
						return (EXIT_FAILURE);
				}
				prev = tmp;
				tmp = tmp->neighbours[i];
				found = 1;
				break;
			}
			i++;
		}
		if (found == 0)
			break;
	}
	if (found == 1)
		set_if_found(&tmp, dst, &prev, map);
	return (EXIT_SUCCESS);
}

static int				solve_conflict_setup(t_subpath **new, t_queue *in_queue,
t_qwrap *qr)
{
	if (*new == NULL)
	{
		delete_path(&in_queue->path);
		remove_queue_item(qr, in_queue);
		return (0);
	}
	if (in_queue->path == NULL)
	{
		delete_path(new);
		return (1);
	}
	return (0);	
}

static int				solve_conflict_sp_setup(t_subpath **new, t_queue *in_queue,
t_qwrap *qr)
{
	if (in_queue->path->segment_len < (*new)->segment_len)
	{
		delete_path(new);
		return (1);
	}
	if (in_queue->path->segment_len > (*new)->segment_len)
	{
		delete_path(&in_queue->path);
		remove_queue_item(qr, in_queue);
		return (0);
	}
	return (0);
}

static int				has_queue_conflict_setup(t_qwrap *qr, t_subpath **pt,
t_room *dst)
{
	t_queue	*iter;

	iter = qr->last;
	while (iter)
	{
		if (iter->dst == dst)
		{
			if (*pt == NULL || iter->path == NULL)
				return (solve_conflict_setup(pt, iter, qr));
			else
				return (solve_conflict_sp_setup(pt, iter, qr));
		}
		iter = iter->prev;
	}
	return (0);
}

static int			new_path_needed(t_room *nb, t_room *src, t_map *map)
{
	if ((nb->checked == 1 &&
	nb->is_conj == 0)
	|| (nb->checked == 0
	&& is_junction(src, nb, map) == 0))
		return (1);
	return (0);
}

static ssize_t		create_path(t_subpath **path, t_room **dst, t_room *nb,
t_map *map)
{
	if (create_new_path(path, NULL, map->end, map) == EXIT_FAILURE
	|| add_rooms_to_path(dst, nb, path, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int			viable_dst(t_room *dst, t_subpath **path, t_room *nb,
t_map *map)
{
	if (dst == NULL)
	{
		delete_path(path);
		return (0);
	}
	if (dst == map->end)
	{
		nb->dead_end = 1;
		delete_path(path);
		return (0);
	}
	return (1);
}

static int			viable_for_queue(t_qwrap *qr, t_room *dst, t_subpath **path)
{
	int	in_q;

	in_q = room_in_bitfield(dst, qr->in_queue);
	if ((in_q == 1 && has_queue_conflict_setup(qr, path, dst) == 0) ||
	in_q == 0)
		return (1);
	return (0);
}

static ssize_t		add_item(t_qwrap *qr, t_subpath **path,
t_room *dst, t_map *map)
{
	if (add_to_queue(qr, map->end, dst, *path) == EXIT_SUCCESS)
	{
		if (dst != map->start)
			add_to_bitfield(dst, qr->in_queue);
		return (EXIT_SUCCESS);
	}
	delete_path(path);
	return (EXIT_FAILURE);
}

static ssize_t		add_items_start(t_qwrap *qr, t_map *map)
{
	size_t			i;
	t_room			*dst;
	t_subpath		*path;

	i = 0;
	dst = NULL;
	while (i < map->end->neighbours_len)
	{
		path = NULL;
		if (map->end->neighbours[i]->dead_end == 0)
		{
			dst = map->end->neighbours[i];
			if (new_path_needed(map->end->neighbours[i], map->end, map) == 1)
			{
				if (create_path(&path, &dst, map->end->neighbours[i], map)
				== EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			if (viable_dst(dst, &path, map->end->neighbours[i], map) == 1
			&& viable_for_queue(qr, dst, &path) == 1)
			{
				if (path)
					dst->weight = map->end->weight + 1;
				if (add_item(qr, &path, dst, map) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static ssize_t	create_queue(t_qwrap **qr, t_map *map)
{
	*qr = (t_qwrap *)malloc(sizeof(t_qwrap));
	if (*qr)
	{
		(*qr)->queue = (t_queue **)malloc(sizeof(t_queue *));
		(*qr)->items = 0;
		(*qr)->last = NULL;
		(*qr)->round = 1;
		if ((*qr)->queue)
		{
			*((*qr)->queue) = NULL;
			map->end->weight = (*qr)->round;
			if (bite_alloc(&((*qr)->in_queue), map) == EXIT_SUCCESS)
				return (EXIT_SUCCESS);
			free ((*qr)->queue);
		}
		free (*qr);
		*qr = NULL;
	}
	return (EXIT_FAILURE);
}

static void		set_weights_nbs_end(t_room *curr)
{
	size_t	i;

	i = 0;
	while (i < curr->neighbours_len)
	{
		curr->neighbours[i]->weight = curr->weight + 1;
		i++;
	}
}

ssize_t		setup_queue(t_qwrap **qr, t_map *map)
{
	if (create_queue(qr, map) == EXIT_SUCCESS)
	{
		set_weights_nbs_end(map->end);
		if (add_items_start(*qr, map) == EXIT_SUCCESS)
		{
			map->end->dead_end = 1;
			// print_queue((*qr));
			// exit (0);
			(*qr)->round++;
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}


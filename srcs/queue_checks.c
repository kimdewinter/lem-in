/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_checks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 14:01:31 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/20 11:11:41 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int				check_length_spe(t_subpath *path, t_room *nb,
t_map *map)
{
	ssize_t	j;

	j = nb->num_options - 1;
	while (j >= 0)
	{
		if (nb->routes[j]->conj == map->end)
		{
			if (path->len + 1 < nb->routes[j]->len)
				return (1);
			return (0);
		}
		j--;
	}
	return (1);
}

static ssize_t			add_rooms_to_path(t_room **dst, t_room *nb,
t_subpath **new, t_map *map, t_queue *item)
{
	t_room	*tmp;
	t_room	*prev;
	size_t	i;
	int		first;
	int		found;
	BITFIELD_TYPE	*in_path;

	prev = NULL;
	tmp = nb;
	*dst = NULL;
	(*new)->sp = 1;
	first = 1;
	if (bite_alloc(&in_path, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (add_to_path(*new, tmp, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (tmp->is_conj == 0 && tmp != map->start)
	{
		i = 0;
		found = 0;
		tmp->weight = 0;
		add_to_bitfield(tmp, in_path);
		while (i < tmp->neighbours_len)
		{
			// printf("nb %s %d\n", tmp->neighbours[i]->name, tmp->neighbours[i]->dead_end);
			if (tmp->neighbours[i] != prev
			&& tmp->neighbours[i]->dead_end == 0
			&& tmp->neighbours[i] != item->dst
			&& tmp->neighbours[i] != item->path->conj
			&& room_in_bitfield(tmp->neighbours[i], in_path) == 0)
			{
				// printf("VIABLE IN ADD %s\n", tmp->neighbours[i]->name);
				if (tmp->neighbours[i]->is_conj == 0
				&& tmp->neighbours[i] != map->start)
				{
					if (add_to_path(*new, tmp->neighbours[i], map)
					== EXIT_FAILURE)
					{
						free (in_path);
						return (EXIT_FAILURE);
					}
					tmp->neighbours[i]->weight = 0;
				}
				prev = tmp;
				tmp = tmp->neighbours[i];
				found = 1;
				first = 0;
				break;
			}
			i++;
		}
		if (found == 0)
		{
			// printf("Found == 0\n");
			break;
		}
	}
	if (found == 1 || first == 1)
	{
		if (tmp != map->start && tmp->weight == 0)
			tmp->weight = item->dst->weight + 1;
		*dst = tmp;
	}
	free (in_path);
	return (EXIT_SUCCESS);
}

static ssize_t	has_queue_conflict(t_qwrap *qr, t_subpath **pt, t_room *dst,
t_room *src, int is_orig_path)
{
	t_queue	*iter;

	iter = qr->last;
	while (iter && iter->handled == 0)
	{
		if (iter->dst == dst && iter->src == src)
		{
			if (*pt == NULL)
			{
				if (iter->path)
				{
					free (iter->path);
					iter->path = NULL;
				}
				remove_queue_item(qr, iter);
				return (0);
			}
			else if (iter->path == NULL)
			{
				if (*pt && is_orig_path == 0)
					free (*pt);
				*pt = NULL;
				return (1);
			}
			else
			{
				if (iter->path->segment_len < (*pt)->segment_len)
				{
					if (*pt && is_orig_path == 0)
						free (*pt);
					*pt = NULL;
					return (1);			
				}
				else if (iter->path->segment_len > (*pt)->segment_len)
				{
					if (iter->path)
					{
						free (iter->path);
						iter->path = NULL;
					}
					remove_queue_item(qr, iter);
					return (0);
				}
			}
		}
		iter = iter->prev;
	}
	return (0);
}

t_room			*nearest_junction(t_room *conj, t_room *nb, t_room *src,
t_map *map, BITFIELD_TYPE *in_path)
{
	t_room	*prev;
	t_room	*tmp;
	size_t	i;
	int		found;

	prev = src;
	tmp = nb;
	found = 1;
	// printf("Before find dst\n");
	while ((tmp->checked == 1 && tmp->is_conj == 0)
	|| (tmp->checked == 0 && is_junction(prev, tmp, map) == 0))
	{
		// printf("We found something %s\n", tmp->name);
		add_to_bitfield(tmp, in_path);
		tmp->is_conj = 0;
		i = 0;
		found = 0;
		while (i < tmp->neighbours_len)
		{
			// printf("i: %lu\n", i);
			// printf("nb %s\n", tmp->neighbours[i]->name);
			if (tmp->neighbours[i]->dead_end == 0
			&& tmp->neighbours[i] != prev
			&& tmp->neighbours[i] != src
			&& tmp->neighbours[i] != tmp
			&& tmp->neighbours[i] != conj
			&& room_in_bitfield(tmp->neighbours[i], in_path) == 0)
			{
				// printf("VIABLE IN FIND DST %s\n", tmp->neighbours[i]->name);
				prev = tmp;
				tmp = tmp->neighbours[i];
				found = 1;
				break;
			}
			i++;
		}
		if (found == 0)
		{
				// printf("After find dst\n");
			return (NULL);
		}
	}
	if (tmp == src && prev)
		prev->dead_end = 1;
	// printf("After find dst\n");
	return (tmp);
}

ssize_t			find_real_nb(t_room *nb, t_queue *item, t_room **dst,
t_map *map)
{
	*dst = nb;
	BITFIELD_TYPE	*in_path;

	if (bite_alloc(&in_path, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*dst = nearest_junction(item->path->conj, nb, item->dst, map, in_path);
	free (in_path);
	return (EXIT_SUCCESS);
}

int				has_overlap(BITFIELD_TYPE *path, BITFIELD_TYPE *room,
t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->bitfield_len)
	{
		if ((path[i] & room[i]) != (BITFIELD_TYPE)0)
			return (1);
		i++;
	}
	return (0);
}

int				is_valid_dst(t_queue *item, t_room *dst, t_room *nb,
size_t round, t_map *map)
{
	(void)round;
	if (dst == NULL)
	{
		nb->dead_end = 1;
		return (0);
	}
	if (dst == item->dst)
	{
		nb->dead_end = 1;
		return (0);
	}
	if (dst == item->path->conj || dst == item->src)
		return (0);
	if (item->dst->weight > dst->weight && dst->weight != 0)
		return (0);
	if ((dst->weight == item->dst->weight) && dst->weight != 0)
	{
		if (has_overlap(item->path->bitconj, dst->bitconj, map) == 1)
		{
			// printf("DST %s %lu ITEM DST %s %lu conj %s\n", dst->name, dst->weight,
			// item->dst->name, item->dst->weight,
			// item->path->conj->name);
			// printf("Not viable because weight round %lu\n", round);
			// print_path(item->path);
			// print_paths(dst);
			return (0);
		}
		// exit (0);
		// return (0);
	}
	return (1);
}

int				is_viable_receiver(t_room *dst, t_queue *item, t_map *map,
t_room *nb)
{
	if (dst->dead_end == 0
	&& dst != item->src
	&& dst != map->end
	&& item->dst != map->end
	&& dst->dead_end == 0
	&& !(item->dst->sps == 1 && nb != map->start)
	&& (room_in_bitfield(dst, item->path->bitconj) == 0))
		return (1);
	return (0);
}

/* Tells whether a path should be added to queue */
static int	solve_path_conflicts_q(t_queue *item, t_room *dst,
t_subpath **new, t_map *map, int is_orig)
{
//	|| ((dst->spe == 1 && item->path->conj == map->end)
	if (dst->spe == 1 && dst != map->start)
	{
		if (check_length_spe(*new, dst, map) == 0)
		{
			if (is_orig == 0)
				delete_path(new);
			add_to_bitfield(item->dst, dst->bitconj);
			return (0);
		}
	}
	if (room_in_bitfield(item->path->conj, dst->bitconj) == 1)
	{
		/* Exclude start?? */
		if (check_length(*new, dst) == 0)
		{
			if (is_orig == 0)
				delete_path(new);
			if (dst != map->start)
				add_to_bitfield(item->dst, dst->bitconj);
			return (0);
		}
		return (1);
	}
	return (1);
}

static ssize_t	add_item_adj(t_queue *item, t_subpath *path, t_room *dst,
t_map *map, t_qwrap *qr)
{
	t_subpath	*final;

	if (path == item->path)
		create_new_path(&final, path, item->dst, map);
	else
		final = path;
	if (add_to_queue(qr, item->dst, dst, final) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	delete_path(&final);
	return (EXIT_FAILURE);
}

ssize_t			add_nb_to_queue(t_map *map, t_queue *item,
t_room *nb, t_qwrap *qr)
{
	t_subpath	*new;
	t_room		*dst;
	int			is_orig_path;

	new = NULL;
	is_orig_path = 1;
	// printf("SRC %s DST %s CONJ %s\n", item->src->name, item->dst->name, item->path->conj->name);
	// print_path(item->path);
	if (find_real_nb(nb, item, &dst, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// if (dst)
	// 	printf("REAL DST%s\n", dst->name);
	if (is_valid_dst(item, dst, nb, qr->round, map) == 0)
	{
		// printf("Not valid dst\n");
		return (EXIT_SUCCESS);
	}
	if (is_viable_receiver(dst, item, map, nb) == 1)
	{
		if (nb->is_conj == 0)
		{
			// printf("Before create path\n");
			if (create_new_path(&new, item->path, item->dst, map)
			== EXIT_FAILURE || add_rooms_to_path(&dst, nb, &new, map, item)
			== EXIT_FAILURE)
				return (EXIT_FAILURE);
			// printf("Real dst %s\n", dst->name);
			is_orig_path = 0;
		}
		else
			new = item->path;
		if (solve_path_conflicts_q(item, dst, &new, map, is_orig_path) == 0)
			return (EXIT_SUCCESS);
		if ((room_in_bitfield(dst, qr->in_queue) == 1
		&& has_queue_conflict(qr, &new, dst, item->dst, is_orig_path) == 0)
		|| (room_in_bitfield(dst, qr->in_queue) == 0))
		{
			add_item_adj(item, new, dst, map, qr);
			if (dst != map->start)
				add_to_bitfield(dst, qr->in_queue);
		}
	}
	return (EXIT_SUCCESS);
}

int			check_length(t_subpath *new_path, t_room *curr)
{
	ssize_t	j;
	size_t	found;

	j = curr->num_options - 1;
	found = 0;
	while (j >= 0)
	{
		if (curr->routes[j]->conj == new_path->conj)
		{
			found++;
			if ((new_path->segment_len + 1) > curr->routes[j]->segment_len)
				return (0);
			else if ((new_path->segment_len + 1) == curr->routes[j]->segment_len
			&& curr->routes[j]->sp == 1)
				return (0);
		}
		j--;
	}
	if (found == 0)
		return (0);
	return (1);
}

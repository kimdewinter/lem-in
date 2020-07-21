/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_find_path.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/21 19:38:39 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/21 19:38:39 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int	is_valid_nb(t_room *tmp, t_room *nb, t_room *prev, t_room *src,
t_map *map)
{
	if (nb->dead_end == 0
	&& nb != prev
	&& nb != src
	&& !(tmp->sps == 1 && nb != map->start)
	&& room_in_bitfield(nb, tmp->unavailable) == 0)
		return (1);
	return (0);
}

static int	find_next_nb(t_room **tmp, t_room **prev, t_room *src, t_map *map)
{
	size_t	i;

	i = 0;
	while (i < (*tmp)->neighbours_len)
	{
		if (is_valid_nb((*tmp), (*tmp)->neighbours[i], *prev, src, map) == 1)
		{	
			(*prev) = (*tmp);
			(*tmp) = (*tmp)->neighbours[i];
			return (1);
		}
		i++;
	}
	return (0);
}

static int	handle_loop(t_room **prev, t_room **nb, t_subpath **new)
{
	(*prev)->dead_end = 1;
	(*nb)->dead_end = 1;
	delete_path(new);
	return (0);	
}

static int	handle_succes(t_room **nb, t_room **src, t_room **dst, t_room *tmp)
{
	add_to_bitfield(*nb, (*src)->unavailable);
	*dst = tmp;
	return (1);	
}

static int	handle_no_options(t_room **nb, t_subpath **new)
{
	delete_path(new);
	(*nb)->dead_end = 1;
	return (0);	
}

int			find_next_path(t_room **dst, t_subpath **new, t_room *nb,
t_room *src, t_map *map)
{
	t_room		*prev;
	t_room		*tmp;
	int			found;

	prev = src;
	tmp = nb;
	found = 1;
	*dst = nb;
	while (is_not_junction(tmp, prev, map) == 1)
	{
		found = 0;
		add_to_bitfield(tmp, prev->unavailable);
		if (add_to_path(*new, tmp, map) == EXIT_FAILURE)
		{
			delete_path(new);
			return (-1);
		}
		found = find_next_nb(&tmp, &prev, src, map);
		if (found == 0)
			return (handle_no_options(&nb, new));
	}
	if (tmp == src)
		return (handle_loop(&prev, &nb, new));
	return (handle_succes(&nb, &src, dst, tmp));
}

int			find_next_dst(t_room *nb, t_queue *item, t_subpath **new,
t_room **dst, t_map *map)
{
	int 		valid;

	valid = -1;
	if (create_new_path(new, NULL, item->dst, map) == EXIT_FAILURE)
		return (valid);
	valid = find_next_path(dst, new, nb, item->dst, map);
	return (valid);
}
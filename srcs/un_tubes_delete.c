/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_tubes_delete.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 14:42:03 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/20 15:31:58 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int			remove_dupl_path(t_connection *side_nb, t_connection *q,
t_map *map, int *changed)
{
	// printf("Remove dupl path\n");
	// print_connection(q);
	// print_connection(side_nb);
	if (side_nb->dist < q->dist)
	{
		*changed = 1;
		remove_path(q, map);
		return (0);
	}
	else
	{
		*changed = 1;
		remove_path(side_nb, map);
		return (1);
	}
}

static int			update_src_path(t_connection *q, t_map *map, int *changed,
size_t *i)
{
	// printf("\n\nUPDATE SRC PATH\n\n");
	if (q->dst->is_junction == 0)
	{
		// printf("Start %s nb %s\n", q->dst->name, q->dst_nb->name);
		// find_real_nb(q);
		if (check_conn(q, i, changed, map) == 0)
		{
			// printf("UPDATE SRC PATH DONE\n");
			return (0);
		}
	}
	// printf("UPDATE SRC PATH DONE\n");
	return (1);
}

static int			is_duplicate_path(t_triangle *tr, t_map *map)
{
	if (tr->side_nb.dst == tr->src_side->src
	&& tr->side_nb.src == tr->src_side->dst
	&& !(tr->src_side->src == map->start
	&& tr->src_side->dst == map->end))
		return (1);
	return (0);
}

static int			handle_conn_removal(size_t *i, t_triangle *tr, int *changed,
t_map *map)
{
	size_t	prev_i;
	t_room	*prev;

	prev_i = 0;
	prev = NULL;
	// printf("\n\nHANDLE CONN REMOVAL\n\n");
	if (check_conn(&tr->side_nb, i, changed, map) == 1)
	{
		if (is_duplicate_path(tr, map) == 1)
		{
			// printf("\n\nIS DUPL PATH\n\n");
			prev_i = *i;
			*i -= remove_dupl_path(&tr->side_nb, tr->src_side, map, changed);
			if (prev_i == *i)
				return (1);
		}
		else if (is_nb_of_src(tr, map, changed) == 1)
		{
			// printf("\n\nREMOVE IF UN\n\n");
			prev = tr->src_side->dst->neighbours[*i];
			remove_if_un(tr, map, changed);
			if (tr->src_side->dst->neighbours[*i] != prev)
				(*i)--;
		}
	}
	// printf("\n\nAFTER HANDLE CONN REMOVAL\n\n");
	return (0);
}

int					del_un_tubes(t_connection *q, int *changed, t_map *map)
{
	size_t			i;
	t_triangle		curr;

	i = 0;
	curr.src_side = q;
	// printf("\n\nDEL UN TUBES\n\n");
	setup_conn(&curr.side_nb, q->dst);
	while (i < q->dst->neighbours_len)
	{
		setup_conn(&curr.side_nb, q->dst);
		if (q->dst->neighbours[i] != q->dst_nb
		&& room_in_bitfield(q->dst->neighbours[i], q->dst->unavailable) == 0)
		{
			set_conn(&curr.side_nb, q->dst->neighbours[i]);
			if (handle_conn_removal(&i, &curr, changed, map) == 1)
				return (1);
			if (update_src_path(q, map, changed, &i) == 0)
				return (1);
		}
		i++;
	}
	// printf("AFTER DEL UN TUBES\n");
	return (1);
}

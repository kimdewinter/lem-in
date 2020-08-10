/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_update_queue.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 13:48:57 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/05 13:48:57 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int		solve_queue_conflict(t_conn_wrap *qr, t_connection *tmp,
t_map *map, size_t added, int *changed)
{
	size_t			i;
	t_connection	*iter;

	i = 0;
	iter = *(qr->q);
	while (iter->next)
		iter = iter->next;
	while (iter && i < added)
	{
		if (iter->dst == tmp->dst
		&& iter->src == tmp->src)
		{
			if (iter->dist > tmp->dist)
			{
				*changed = 1;
				del_tube(iter->dst, iter->dst_nb, map);
				del_tube(iter->dst_nb, iter->dst, map);
				del_tube(iter->src, iter->src_nb, map);
				del_tube(iter->src_nb, iter->src, map);
				remove_q_item_un(qr, iter);
				tmp->add = 1;
				return (0);
			}
			else
			{
				*changed = 1;
				del_tube(tmp->dst, tmp->dst_nb, map);
				del_tube(tmp->dst_nb, tmp->dst, map);
				del_tube(tmp->src, tmp->src_nb, map);
				del_tube(tmp->src_nb, tmp->src, map);
				tmp->add = 0;
				return (1);
			}
		}
		i++;
		iter = iter->prev;
	}
	return (0);
}

static ssize_t			un_add_nbs_to_queue(t_room *start, t_conn_wrap *qr,
t_map *map, int *changed)
{
	size_t			i;
	t_connection	tmp;
	BITFIELD_TYPE	*added_to_queue;
	size_t			added;

	i = 0;
	added = 0;
	printf("\n\nADJUST QUEUE\n");
	printf("START %s\n", start->name);
	if (start == map->end)
		return (EXIT_SUCCESS);
	if (bite_alloc(&added_to_queue, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	setup_conn(&tmp, start);
	while (i < start->neighbours_len)
	{
		setup_conn(&tmp, start);
		if (start->neighbours[i] != NULL)
		{
			tmp.add = 1;
			set_conn(&tmp, start->neighbours[i]);
			// printf("Candidate %s\n", start->neighbours[i]->name);
			if (tmp.dst->is_junction == 0)
			{
				// printf("Dst != junction\n");
				// print_connection(&tmp);
				find_real_nb(&tmp, map);
			}
			// if (tmp.dst)
			// 	printf("Real nb: %s\n", tmp.dst->name);
			if (tmp.dst == start)
			{
				printf("Loop\n");
				*changed = 1;
				del_tube(start->neighbours[i], start, map);
				i -= del_tube(start, start->neighbours[i], map);
				del_tube(start, tmp.dst_nb, map);
				del_tube(tmp.dst_nb, start, map);
			}
			else if (tmp.dst == NULL)
			{
				printf("Nowhere to go\n");
				*changed = 1;
				del_tube(start->neighbours[i], start, map);
				i -= del_tube(start, start->neighbours[i], map);
			}
			else if (room_in_bitfield(tmp.dst, qr->visited) == 0)
			{
				if (room_in_bitfield(tmp.dst, added_to_queue) == 1)
				{
					printf("Already a dst added to queue\n");
					i -= solve_queue_conflict(qr, &tmp, map, added,
					changed);
					// printf("After solve queue confl\n");
				}
				if (tmp.add == 1)
				{
					// printf("Add to queue\n");
					if (add_q_item_un(qr, &tmp) == EXIT_FAILURE)
						return (EXIT_FAILURE);
					added++;
					// add_to_bitfield(tmp.dst, visited);
					add_to_bitfield(tmp.dst, added_to_queue);
				}
			}
		}
		i++;
	}
	add_to_bitfield(start, qr->visited);
	free (added_to_queue);
	return (EXIT_SUCCESS);
}

// static void	set_dsts_to_visited(t_conn_wrap *qr, size_t len)
// {
// 	t_connection	*iter;
// 	size_t			i;
// 	t_connection	*prev;

// 	iter = *(qr->q);
// 	i = 0;
// 	while (iter && i < len)
// 	{
// 		add_to_bitfield(iter->dst, qr->visited);
// 		prev = iter;
// 		iter = iter->next;
// 		i++;
// 		remove_q_item_un(qr, prev);
// 	}
// }

ssize_t		update_queue_un(t_conn_wrap *qr, t_map *map, int *changed)
{
	size_t			len;
	size_t			i;
	t_connection	*iter;
	t_connection	*prev;

	printf("Update queue\n");
	iter = *(qr->q);
	len = qr->items;
	i = 0;
	// printf("ROUND %lu len %lu\n", qr->round, qr->items);
	printf("Len %lu\n", len);
	while (i < len && iter)
	{
		if (room_in_bitfield(iter->dst, qr->visited) == 0)
		{
			if (un_add_nbs_to_queue(iter->dst, qr, map, changed) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		prev = iter;
		iter = iter->next;
		remove_q_item_un(qr, prev);
		i++;
	}
	return (EXIT_SUCCESS);
	// set_dsts_to_visited(qr, len);
	// print_connection_queue(qr->q);
	// if (qr->round == 5)
	// 	exit (0);
}
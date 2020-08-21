/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traverse_bf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/02 19:04:32 by kim           #+#    #+#                 */
/*   Updated: 2020/08/21 16:42:35 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

inline static void	add_nb_to_q(t_qwrap *queue,
								t_room *room)
{
	t_qnode	*curr;

	curr = (t_qnode *)malloc(sizeof(t_qnode) * 1);
	if (curr != NULL)
	{
		curr->prev = queue->tail;
		curr->next = NULL;
		curr->room = room;
		if (curr->prev != NULL)
			curr->prev->next = curr;
		queue->tail = curr;
	}
}

static ssize_t		add_nbs_to_q(t_qwrap *queue,
								t_room *room,
								const size_t call_code)
{
	size_t	i;

	i = 0;
	while (i < room->neighbours_len)
	{
		if ((call_code == LVL_GRPH_E2S &&
			room->neighbours[i]->dist_to_end == -1) ||
			(call_code == LVL_GRPH_S2E &&
			room->neighbours[i]->dist_to_start == -1 &&
			room->neighbours[i]->dist_to_end != -1))
		{
			add_nb_to_q(queue, room->neighbours[i]);
			if (queue->tail == NULL || queue->tail->room != room->neighbours[i])
				return (handle_err_route_finder(1, "add_nb_to_q\n"));
			if (call_code == LVL_GRPH_E2S)
				queue->tail->room->dist_to_end = room->dist_to_end + 1;
			else if (call_code == LVL_GRPH_S2E)
				queue->tail->room->dist_to_start = room->dist_to_start + 1;
			if (queue->head == NULL)
				queue->head = queue->tail;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static ssize_t		exec_traverse_bf(t_qwrap *queue,
										const size_t call_code,
										const t_map *map)
{
	while (queue->head != NULL)
	{
		if (!(queue->head->room == map->start && call_code == LVL_GRPH_E2S))
		{
			if (add_nbs_to_q(
				queue, queue->head->room, call_code) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		if (queue->head->next == NULL)
		{
			free(queue->head);
			queue->head = NULL;
			queue->tail = NULL;
			return (EXIT_SUCCESS);
		}
		else
		{
			queue->head = queue->head->next;
			free(queue->head->prev);
			queue->head->prev = NULL;
		}
	}
	return (handle_err_route_finder(0, "exec_traverse_bf\n"));
}

ssize_t				traverse_bf(t_room *room_to_begin_from,
								const size_t call_code,
								const t_map *map)
{
	t_qwrap	queue;

	queue.head = NULL;
	queue.tail = NULL;
	if (call_code == LVL_GRPH_E2S)
		room_to_begin_from->dist_to_end = 0;
	else
		room_to_begin_from->dist_to_start = 0;
	if (add_nbs_to_q(&queue, room_to_begin_from, call_code) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (exec_traverse_bf(&queue, call_code, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
/*
** call_codes:
** LVL_GRPH_E2S is level-graph from end->start (set distance from end)
** LVL_GRPH_S2E is level-graph from start->end (set distance from start)
*/

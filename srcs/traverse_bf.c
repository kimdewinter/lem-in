/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traverse_bf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/02 19:04:32 by kim           #+#    #+#                 */
/*   Updated: 2020/08/03 15:54:54 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

inline static void	add_nb_to_q(t_qwrap *queue, t_room *room)
{
	t_qnode	*curr;

	curr = (t_qnode *)malloc(sizeof(t_qnode) * 1);
	if (curr != NULL)
	{
		curr->prev = queue->tail;
		curr->next = NULL;
		curr->room = room;
		if (queue->tail != NULL)
			queue->tail->next = curr;
		queue->tail = curr;
	}
}

static ssize_t	add_nbs_to_q(t_qwrap *queue, t_room *room)
{
	size_t	i;

	i = 0;
	while (i < room->neighbours_len)
	{
		add_nb_to_q(queue, room->neighbours[i]);
		if (queue->tail == NULL || queue->tail->room != room->neighbours[i])
			return (handle_err_route_finder(1, "add_nb_to_q\n"));
		if (queue->head == NULL)
			queue->head = queue->tail;
		i++;
	}//adding the rest of the neighbours
	return (EXIT_SUCCESS);
}

static ssize_t		exec_traverse_bf(t_qnode *curr,
										t_qwrap *queue,
										t_map *map)
{
	if (add_nbs_to_q(queue, curr->room) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (curr->next == NULL)//if true, this was the last node
	{
		queue->head = NULL;
		queue->tail = NULL;
		free(curr);
		curr = NULL;
		return (EXIT_SUCCESS);
	}
	else
	{
		queue->head = curr->next;
		queue->head->prev = NULL;
		free(curr);
		curr = NULL;
		return (exec_traverse_bf(queue->head, queue, map));
	}
}//TO DO: add an actual operation when traversing a room

ssize_t				traverse_bf(t_map *map, t_room *room_to_begin_from)
{
	t_qwrap	queue;

	queue.head = NULL;
	queue.tail = NULL;
	set_visited(map->rooms->entries, map->rooms->size, 0);//set all rooms to unvisited
	room_to_begin_from->visited = 1;//set start/end room to visited
	if (add_nbs_to_q(&queue, room_to_begin_from) == EXIT_FAILURE)//put neighbours of start/end in queue
		return (EXIT_FAILURE);
	if (exec_traverse_bf(queue.head, &queue, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

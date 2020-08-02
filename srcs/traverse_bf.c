/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traverse_bf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/02 19:04:32 by kim           #+#    #+#                 */
/*   Updated: 2020/08/02 20:50:43 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

inline static t_qnode	*add_nb_to_q(t_qnode **tail, t_room *room)
{
	t_qnode	*curr;

	curr = (t_qnode *)malloc(sizeof(t_qnode) * 1);
	if (curr == NULL)
	curr->prev = (*tail == NULL) ? NULL : *tail;
	curr->next = NULL;
	curr->data = room;
	if (*tail != NULL)
		(*tail)->next = curr;
	*tail = curr;
}

static t_qnode		*add_nbs_to_q(t_qnode **head, t_qnode **tail, t_room *room)
{
	size_t	i;

	i = 0;
	if (i < room->neighbours_len)
	{
		add_nb_to_q(tail, room->neighbours[i]);
		if (*tail == NULL || (*tail)->data != room->neighbours[i])
			return (handle_err_route_finder(1, "add_nb_to_q\n"));
		if (*head == NULL)
			*head = *tail;
		i++;
	}//setting up the head with the first nb, separate from while loop to save unnecessary if-checks
	while (i < room->neighbours_len)
	{
		add_nb_to_q(tail, room->neighbours[i]);
		if (*tail == NULL || (*tail)->data != room->neighbours[i])
			return (handle_err_route_finder(1, "add_nb_to_q\n"));
		i++;
	}//adding the rest of the neighbours
}

ssize_t				traverse_bf(t_map *map, t_room *room_to_begin_from)
{
	t_qnode	*head;
	t_qnode	*tail;

	head = NULL;
	tail = NULL;
	set_visited(map->rooms->entries, map->rooms->size, 0);
	room_to_begin_from->visited = 1;
	if (add_nbs_to_q(&head, &tail, room_to_begin_from) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	//PLACEHOLDER: more to follow
}
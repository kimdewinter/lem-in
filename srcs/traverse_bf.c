/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traverse_bf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/02 19:04:32 by kim           #+#    #+#                 */
/*   Updated: 2020/08/03 13:03:58 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

inline static void	add_nb_to_q(t_qnode **tail, t_room *room)
{
	t_qnode	*curr;

	curr = (t_qnode *)malloc(sizeof(t_qnode) * 1);
	if (curr != NULL)
	{
		curr->prev = (*tail == NULL) ? NULL : *tail;
		curr->next = NULL;
		curr->data = room;
		if (*tail != NULL)
			(*tail)->next = curr;
		*tail = curr;
	}
}

static t_qnode		*add_nbs_to_q(t_qnode **head, t_qnode **tail, t_room *room)
{
	size_t	i;

	i = 0;
	while (i < room->neighbours_len)
	{
		add_nb_to_q(tail, room->neighbours[i]);
		if (*tail == NULL || (*tail)->data != room->neighbours[i])
			return (handle_err_route_finder(1, "add_nb_to_q\n"));
		if (*head == NULL)
			*head = *tail;
		i++;
	}//adding the rest of the neighbours
}

ssize_t				traverse_bf(t_map *map, t_room *room_to_begin_from)
{
	t_qnode	*head;
	t_qnode	*tail;

	head = NULL;
	tail = NULL;
	set_visited(map->rooms->entries, map->rooms->size, 0);//set all rooms to unvisited
	room_to_begin_from->visited = 1;//set start/end room to visited
	if (add_nbs_to_q(&head, &tail, room_to_begin_from) == EXIT_FAILURE)//put neighbours of start/end in queue
		return (EXIT_FAILURE);
	//PLACEHOLDER: more to follow
}

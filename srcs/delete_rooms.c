/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_rooms.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 15:19:42 by kim           #+#    #+#                 */
/*   Updated: 2020/07/26 19:20:01 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

inline static void	delete_ptr(void **arr)
{
	free(*arr);
	*arr = NULL;
}

static void			delete_single_room(t_room *room)
{
	size_t	i;

	if (room->routes != NULL)
	{
		i = 0;
		while (i < room->num_options)
		{
			if (room->routes[i] != NULL)
			{
				if (room->routes[i]->path != NULL)
					delete_ptr((void **)&room->routes[i]->path);
				if (room->routes[i]->bitconj != NULL)
					delete_ptr((void **)&room->routes[i]->bitconj);
				free(room->routes[i]);//does this have a chance of double-free?
				room->routes[i] = NULL;
			}
			i++;
		}
		delete_ptr((void **)&room->routes);
	}
	if (room->name != NULL)
		delete_ptr((void **)&room->name);
	if (room->neighbours != NULL)
		delete_ptr((void **)&room->neighbours);
	if (room->bitconj != NULL)
		delete_ptr((void **)&room->bitconj);
}

void				delete_all_rooms(t_table *rooms)
{
	size_t	i;

	i = 0;
	while (i < rooms->size)
	{
		if (rooms->entries[i] != NULL)
		{
			delete_single_room(rooms->entries[i]->val);
			delete_ptr((void **)&rooms->entries[i]->val);
		}
		i++;
	}
}

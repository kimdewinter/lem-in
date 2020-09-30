/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_rooms.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 15:19:42 by kim           #+#    #+#                 */
/*   Updated: 2020/09/30 16:40:56 by simoncleerd   ########   odam.nl         */
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
	if (room->name != NULL)
		delete_ptr((void **)&room->name);
	if (room->neighbours != NULL)
		delete_ptr((void **)&room->neighbours);
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

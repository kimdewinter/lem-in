/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   room_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 15:44:56 by kim           #+#    #+#                 */
/*   Updated: 2020/08/02 17:48:18 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t			setup_room(t_room **dest,
							const char *name,
							const ssize_t xpos,
							const ssize_t ypos,
							size_t *num_room)
{
	t_room	*room;

	room = (t_room *)malloc(sizeof(t_room));
	if (room != NULL && name != NULL)
	{
		room->room_i = *num_room;
		room->is_junction = 0;
		room->weight = 0;
		room->spe = 0;
		room->sps = 0;
		room->bitroom = NULL;
		room->name = (char *)name;
		room->xpos = xpos;
		room->ypos = ypos;
		room->neighbours_len = 0;
		room->neighbours = NULL;
		room->ant = 0;
		*dest = room;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static ssize_t	add_neighbour_new(t_room *room)
{
	if (room != NULL && room->neighbours_len == 0 && room->neighbours == NULL)
	{
		room->neighbours = (t_room **)malloc(sizeof(t_room *) * 1);
		if (room->neighbours != NULL)
		{
			room->neighbours[0] = NULL;
			room->neighbours_len++;
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}//creates a new room->neighbours char** array of 1 cell

static ssize_t	add_neighbour_grow(t_room *room)
{
	t_room	**new_neighbours;
	size_t	i;

	new_neighbours = NULL;
	i = 0;
	if (room != NULL && room->neighbours_len > 0 && room->neighbours != NULL)
	{
		new_neighbours = (t_room **)malloc(sizeof(t_room *)
			* (room->neighbours_len + 1));
		if (new_neighbours != NULL)
		{
			while (i < room->neighbours_len)
			{
				new_neighbours[i] = room->neighbours[i];
				i++;
			}
			new_neighbours[i] = NULL;
			free(room->neighbours);
			room->neighbours = new_neighbours;
			room->neighbours_len++;
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}//expands the room->neighbours char** array by 1

ssize_t			add_neighbour(t_room *room, t_room *neighbour)
{
	if (room != NULL && neighbour != NULL)
	{
		if (room->neighbours_len == 0 && room->neighbours == NULL &&
			add_neighbour_new(room) == EXIT_SUCCESS)
		{
			room->neighbours[room->neighbours_len - 1] = neighbour;
			if (room->neighbours[room->neighbours_len - 1] != NULL)
				return (EXIT_SUCCESS);
		}//handles when room->neighbours t_room** array is yet to be made
		else if (room->neighbours_len > 0 && room->neighbours != NULL &&
					add_neighbour_grow(room) == EXIT_SUCCESS)
		{
			room->neighbours[room->neighbours_len - 1] = neighbour;
			if (room->neighbours[room->neighbours_len - 1] != NULL)
				return (EXIT_SUCCESS);
		}//handles when room->neighbours t_room** array needs to grow by 1
	}
	return (EXIT_FAILURE);
}

ssize_t			purge_room(t_room **room)
{
	if (*room != NULL)
	{
		if ((*room)->name != NULL)
		{
			free((*room)->name);
			(*room)->name = NULL;
		}
		(*room)->xpos = -1;
		(*room)->ypos = -1;
		while ((*room)->neighbours_len > 0)
		{
			(*room)->neighbours_len--;
			if ((*room)->neighbours[(*room)->neighbours_len] != NULL)
			{
				free((*room)->neighbours[(*room)->neighbours_len]);
				(*room)->neighbours[(*room)->neighbours_len] = NULL;
			}
		}
		(*room)->ant = -1;
		free(*room);
		*room = NULL;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
/*
** resets a room's variables to their default states,
** frees all underlying allocated space(s)
** and finally the room itself
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   roomutils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 15:44:56 by kim           #+#    #+#                 */
/*   Updated: 2020/04/28 15:54:56 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

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
		room->name = (char *)name;
		room->xpos = xpos;
		room->ypos = ypos;
		room->neighbours_len = 0;
		room->neighbours = NULL;
		room->ant = 0;
		room->room_i = *num_room;
		room->bitroom = NULL;
		// room->routes = NULL;
		// room->routes_len = 0;
		room->this_i = 0;
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

ssize_t	add_neighbour(t_table *table, t_room *room, char *neighbour)
{
	if (room != NULL && neighbour != NULL)
	{
		if (room->neighbours_len == 0 && room->neighbours == NULL && add_neighbour_new(room) == EXIT_SUCCESS)
		{
			room->neighbours[room->neighbours_len - 1] = (t_room *)search_ht(table, neighbour);
			if (room->neighbours[room->neighbours_len - 1] != NULL)
				return (EXIT_SUCCESS);
		}//handles when room->neighbours char** array is yet to be made
		else if (room->neighbours_len > 0 && room->neighbours != NULL && add_neighbour_grow(room) == EXIT_SUCCESS)
		{
			room->neighbours[room->neighbours_len - 1] = (t_room *)search_ht(table, neighbour);
			if (room->neighbours[room->neighbours_len - 1] != NULL)
				return (EXIT_SUCCESS);
		}//handles when room->neighbours char** array needs to grow by 1
	}
	return (EXIT_FAILURE);
}

ssize_t	purge_room(t_room **room)
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
}//resets a room's variables to their default states, frees all underlying allocated space(s), and finally the room itself

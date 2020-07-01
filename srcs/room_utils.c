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
		room->weight = 0;
		room->dead_end = 0;
		room->is_conj = 0;
		room->checked = 0;
		room->viable_nbs = 0;
		room->sps = 0;
		room->spe = 0;
		room->viable = NULL;
		room->viable_items = 0;
		room->viable_size = 0;
		room->room_i = *num_room;
		room->bitconj = NULL;
		room->name = (char *)name;
		room->xpos = xpos;
		room->ypos = ypos;
		room->neighbours_len = 0;
		room->neighbours = NULL;
		room->ant = 0;
		room->num_options = 0;
		room->routes_size = 0;
		room->routes = NULL;
		*dest = room;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static ssize_t	add_neighbour_new(t_room *room)
{
	if (room != NULL && room->neighbours_len == 0 && room->neighbours == NULL)
	{
		room->neighbours = (t_neighbour **)malloc(sizeof(t_neighbour *) * 1);
		if (room->neighbours != NULL)
		{
			room->neighbours[0] = (t_neighbour *)malloc(sizeof(t_neighbour));
			if (room->neighbours[0])
			{
				room->neighbours[0]->nb = (t_room *)malloc(sizeof(t_room) * 1);
				if (room->neighbours[0]->nb)
				{
					room->neighbours[0]->nb = NULL;
					room->neighbours[0]->available = 1;
					room->neighbours_len++;
					return (EXIT_SUCCESS);
				}
			}
		}
	}
	return (EXIT_FAILURE);
}//creates a new room->neighbours char** array of 1 cell

static ssize_t	add_neighbour_grow(t_room *room)
{
	t_neighbour	**new_neighbours;
	size_t	i;

	new_neighbours = NULL;
	i = 0;
	if (room != NULL && room->neighbours_len > 0 && room->neighbours != NULL)
	{
		new_neighbours = (t_neighbour **)malloc(sizeof(t_neighbour *)
			* (room->neighbours_len + 1));
		if (new_neighbours != NULL)
		{
			while (i < room->neighbours_len)
			{
				new_neighbours[i] = room->neighbours[i];
				i++;
			}
			new_neighbours[i] = (t_neighbour *)malloc(sizeof(t_neighbour));
			if (new_neighbours[i])
			{
				new_neighbours[i]->nb = (t_room *)malloc(sizeof(t_room));
				if (new_neighbours[i]->nb != NULL)
				{
					new_neighbours[i]->available = 1;
					free(room->neighbours);
					room->neighbours = new_neighbours;
					room->neighbours_len++;
					return (EXIT_SUCCESS);
				}
			}
		}
	}
	return (EXIT_FAILURE);
}//expands the room->neighbours char** array by 1

ssize_t	add_neighbour(t_room *room, t_room *neighbour)
{
	if (room != NULL && neighbour != NULL)
	{
		if (room->neighbours_len == 0 && room->neighbours == NULL && add_neighbour_new(room) == EXIT_SUCCESS)
		{
			room->neighbours[room->neighbours_len - 1]->nb = neighbour;
			if (room->neighbours[room->neighbours_len - 1] != NULL)
			{
				room->viable_nbs++;
				return (EXIT_SUCCESS);
			}
		}//handles when room->neighbours t_room** array is yet to be made
		else if (room->neighbours_len > 0 && room->neighbours != NULL && add_neighbour_grow(room) == EXIT_SUCCESS)
		{
			room->neighbours[room->neighbours_len - 1]->nb = neighbour;
			if (room->neighbours[room->neighbours_len - 1] != NULL)
			{
				room->viable_nbs++;
				return (EXIT_SUCCESS);
			}
		}//handles when room->neighbours t_room** array needs to grow by 1
	}
	return (EXIT_FAILURE);
}

// ssize_t		add_neighbour(t_room *room, t_room *nb, t_map *map)
// {
// 	size_t	i;

// 	i = 0;
// 	if (room->neighbours = NULL && room->neighbours_len == 0)
// 	{
// 		room->neighbours = (t_neighbour **)malloc(sizeof(t_neighbour *) * map->rooms->count);
// 		if (room->neighbours)
// 		{
// 			while (i < map->rooms->count)
// 			{
// 				room->neighbours[i] = NULL;
// 				i++;
// 			}
// 			room->neighbours[nb->room_i] = (t_neighbour *)malloc(sizeof(t_neighbour));
// 			if (room->neighbours[nb->room_i])
// 			{
// 				room->neighbours[0]->nb = nb;
// 				room->neighbours[0]->available = 1;
// 			}
// 		}
// 	}
// 	else
// 	{
		
// 	}
// 	room->neighbours_len++;	
// }

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

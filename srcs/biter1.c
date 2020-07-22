/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   biter1.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:13:42 by kim           #+#    #+#                 */
/*   Updated: 2020/07/22 16:52:22 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		room_in_bitfield(t_room *curr, BITFIELD_TYPE *bitfield)
{
	if ((bitfield[curr->room_i / BITFIELD_SIZE] &
	((BITFIELD_TYPE)1 << (63 - curr->room_i % BITFIELD_SIZE)))
	!= (BITFIELD_TYPE)0)
		return (1);
	return (0);
}

void	add_to_bitfield(t_room *curr, uint64_t *bitfield)
{
	bitfield[curr->room_i / BITFIELD_SIZE] |=
	((BITFIELD_TYPE)1 << (63 - curr->room_i % BITFIELD_SIZE));
}

ssize_t	bite_alloc(BITFIELD_TYPE **dst, const t_map *map)
{
	size_t	i;

	*dst =
		(BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * map->bitfield_len);
	if (*dst == NULL)
		return (handle_err_biter(1, "bite_alloc\n"));
	i = 0;
	while (i < map->bitfield_len)
	{
		(*dst)[i] = (BITFIELD_TYPE)0;
		i++;
	}
	return (EXIT_SUCCESS);
}

ssize_t	bite_alloc_noval(BITFIELD_TYPE **dst, const t_map *map)
{
	*dst =
		(BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * map->bitfield_len);
	if (*dst == NULL)
		return (handle_err_biter(1, "bite_alloc_noval\n"));
	return (EXIT_SUCCESS);
}

ssize_t	bite_room_new(t_room *room, const t_map *map)
{
	size_t	i;

	i = room->room_i / BITFIELD_SIZE;
	if (room != NULL && room->bitroom == NULL &&
		bite_alloc(&(room->bitroom), map) == EXIT_SUCCESS)
	{
		room->bitroom[i] = (BITFIELD_TYPE)1 <<
		((BITFIELD_SIZE - 1) - room->room_i % BITFIELD_SIZE);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
/*
** takes a room and stores it's bitfield-form in room->bitroom
*/

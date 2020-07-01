/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   biter2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 16:01:15 by kim           #+#    #+#                 */
/*   Updated: 2020/07/01 13:24:52 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			add_conj_to_bitroute(t_room *conj, BITFIELD_TYPE *bitconj)
{
	bitconj[conj->room_i / BITFIELD_SIZE] |=
	((BITFIELD_TYPE)1 << (63 - conj->room_i % BITFIELD_SIZE));	
}

ssize_t			bite_bitroute_copy(BITFIELD_TYPE *dst,
									const BITFIELD_TYPE *src,
									const t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->bitfield_len)
	{
		if (dst == NULL || src == NULL)
			return (handle_err_biter(0, "bite_bitroute_copy\n"));
		dst[i] = src[i];
		i++;
	}
	return (EXIT_SUCCESS);
}
/*
** copies a bitfield-form route
*/

ssize_t			bite_bitroute_merge(BITFIELD_TYPE *dst,
									const BITFIELD_TYPE *src1,
									const BITFIELD_TYPE *src2,
									const t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->bitfield_len)
	{
		dst[i] = src1[i] | src2[i];
		i++;
	}
	return (EXIT_SUCCESS);
}
/*
** copies a bitfield-form route
*/

ssize_t			bite_bitroute_bzero(BITFIELD_TYPE *bitroute, const t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->bitfield_len)
	{
		bitroute[i] = (BITFIELD_TYPE)0;
		i++;
	}
	return (EXIT_SUCCESS);
}

size_t			copy_bitconj(BITFIELD_TYPE **dst, BITFIELD_TYPE *src,
t_map *map)
{
	size_t	i;

	i = 0;
	if (bite_alloc(dst, map) == EXIT_SUCCESS)
	{
		while (i < map->bitfield_len)
		{
			(*dst)[i] = src[i];
			i++;
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

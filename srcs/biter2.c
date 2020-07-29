/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   biter2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 16:01:15 by kim           #+#    #+#                 */
/*   Updated: 2020/07/29 15:42:41 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

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

ssize_t			bite_biteroute_allocmerge(BITFIELD_TYPE **dst,
											const BITFIELD_TYPE *src1,
											const BITFIELD_TYPE *src2,
											const t_map *map)
{
	size_t	i;

	*dst = (BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * BITFIELD_SIZE);
	if (*dst == NULL)
		return (handle_err_biter(1, "bite_biteroute_allocmerge\n"));
	i = 0;
	while (i < map->bitfield_len)
	{
		(*dst)[i] = src1[i] | src2[i];
		i++;
	}
	return (EXIT_SUCCESS);
}

ssize_t			bite_add_room_to_bitfield(BITFIELD_TYPE **dst,
											const BITFIELD_TYPE *src,
											const t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->bitfield_len)
	{
		(*dst)[i] |= src[i];
		i++;
	}
	return (EXIT_SUCCESS);
}

ssize_t			allocopy_bitfield(BITFIELD_TYPE **dst,
									BITFIELD_TYPE *src,
									t_map *map)
{
	size_t	i;

	i = 0;
	if (bite_alloc_noval(dst, map) == EXIT_SUCCESS)
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

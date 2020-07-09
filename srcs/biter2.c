/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   biter2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 16:01:15 by kim           #+#    #+#                 */
/*   Updated: 2020/07/09 16:41:38 by kim           ########   odam.nl         */
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

ssize_t			bite_bitroute_merge(BITFIELD_TYPE **dst,
									const BITFIELD_TYPE *src1,
									const BITFIELD_TYPE *src2,
									const t_map *map)
{
	size_t	i;

	*dst = (BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * BITFIELD_SIZE);
	if (*dst == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < map->bitfield_len)
	{
		(*dst)[i] = src1[i] | src2[i];
		i++;
	}
	return (EXIT_SUCCESS);
}

size_t			copy_bitconj(BITFIELD_TYPE **dst,
							BITFIELD_TYPE *src,
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

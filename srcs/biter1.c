/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   biter1.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:13:42 by kim           #+#    #+#                 */
/*   Updated: 2020/06/23 19:21:07 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

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
		*dst[i] = (BITFIELD_TYPE)0;
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

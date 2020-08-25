/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder_utils3.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/02 19:20:25 by kim           #+#    #+#                 */
/*   Updated: 2020/08/25 14:08:14 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	alloc_single_blank_route_helper(t_route **dst,
												const size_t bitroute_len)
{
	size_t	i;

	if (*dst != NULL)
	{
		if ((*dst)->bitroute != NULL && (*dst)->route != NULL)
		{
			i = 0;
			while (i < (*dst)->len)
			{
				if (i < bitroute_len)
					(*dst)->bitroute[i] = (BITFIELD_TYPE)0;
				(*dst)->route[i] = NULL;
				i++;
			}
			return (EXIT_SUCCESS);
		}
		else
		{
			if ((*dst)->bitroute != NULL)
				free((*dst)->bitroute);
			if ((*dst)->route != NULL)
				free((*dst)->route);
			free(*dst);
			*dst = NULL;
		}
	}
	return (EXIT_FAILURE);
}

ssize_t			alloc_single_blank_route(t_route **dst,
											const size_t route_len,
											const size_t bitroute_len)
{
	*dst = (t_route *)malloc(sizeof(t_route) * 1);
	if (*dst != NULL)
	{
		(*dst)->len = route_len;
		(*dst)->used = 0;
		(*dst)->ants = 0;
		(*dst)->bitroute =
			(BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * bitroute_len);
		(*dst)->route = (t_room **)malloc(sizeof(t_room *) * route_len);
		return (alloc_single_blank_route_helper(dst, bitroute_len));
	}
	return (EXIT_FAILURE);
}

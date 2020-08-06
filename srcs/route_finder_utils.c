/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_finder_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/02 19:20:25 by kim           #+#    #+#                 */
/*   Updated: 2020/08/06 18:18:15 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t			alloc_single_blank_route(t_route **dst,
											const size_t route_len,
											const size_t bitroute_len)
{
	size_t	i;

	*dst = (t_route *)malloc(sizeof(t_route) * 1);
	if (*dst != NULL)
	{
		(*dst)->len = route_len;
		(*dst)->used = 0;
		(*dst)->ants = 0;
		(*dst)->bitroute =
			(BITFIELD_TYPE *)malloc(sizeof(BITFIELD_TYPE) * bitroute_len);
		(*dst)->route = (t_room **)malloc(sizeof(t_room *) * route_len);
		if ((*dst)->bitroute != NULL && (*dst)->route != NULL)
		{
			i = 0;
			while (i < route_len)
			{
				if (i < bitroute_len)
					(*dst)->bitroute[i] = (BITFIELD_TYPE)0;
				(*dst)->route[i] = NULL;
				i++;
			}
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
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

ssize_t				alloc_multiple_blank_routes(t_route ***dst,
												const size_t route_num,
												const size_t route_len,
												const size_t bitroute_len)
{
	size_t	i;

	*dst = (t_route **)malloc(sizeof(t_route *) * route_num);
	if (*dst == NULL)
		return (handle_err_route_finder(1, "alloc_multiple_blank_routes\n"));
	i = 0;
	while (i < route_num)
	{
		alloc_single_blank_route(dst[i], route_len, bitroute_len);
		if (dst[i] == NULL)
			return (handle_err_route_finder(1,
				"alloc_multiple_blank_routes\n"));
		i++;
	}
	return (EXIT_SUCCESS);
}

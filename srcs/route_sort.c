/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_sort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 19:37:06 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/29 19:37:06 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		swap_paths(t_room *dst, size_t i, size_t j)
{
	t_subpath	*tmp;

	tmp = dst->routes[i];
	dst->routes[i] = dst->routes[j];
	dst->routes[j] = tmp;
}

void		sort_paths(t_room *room, size_t start_ind)
{
	size_t	swapped;
	size_t	i;

	swapped = 1;
	i = start_ind;
	while (swapped != 0)
	{
		i = start_ind;
		swapped = 0;
		while (i + 1 < room->num_options)
		{
			if (room->routes[i]->len > room->routes[i + 1]->len)
			{
				swap_paths(room, i, i + 1);
				swapped++;
			}
			i++;
		}
	}
}
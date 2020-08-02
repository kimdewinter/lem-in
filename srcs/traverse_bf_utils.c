/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traverse_bf_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/02 19:04:32 by kim           #+#    #+#                 */
/*   Updated: 2020/08/02 19:55:12 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			set_visited(t_room **rooms, size_t len, size_t set_to)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (rooms[i] != NULL)
			rooms[i]->visited = set_to;
		i++;
	}
}

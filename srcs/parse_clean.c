/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_clean.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 20:18:40 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/29 20:17:25 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	free_room_names(char **rooms)
{
	size_t	i;

	i = 0;
	while (rooms[i] != NULL)
	{
		free(rooms[i]);
		i++;
	}
	free(rooms);
}

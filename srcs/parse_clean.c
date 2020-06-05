/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_clean.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 20:18:40 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/04 20:19:52 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void	free_room_names(char **rooms)
{
	size_t	i;

	i = 0;
	while (rooms[i] != NULL)
	{
		free (rooms[i]);
		i++;
	}
	free (rooms);
}
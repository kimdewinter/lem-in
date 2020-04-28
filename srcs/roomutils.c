/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   roomutils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 15:44:56 by kim           #+#    #+#                 */
/*   Updated: 2020/04/28 15:54:56 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"
# include "../libftprintf/includes/libftprintf.h"
# include "../libftprintf/libft/libft.h"
# include "../libftprintf/libft/get_next_line.h"

ssize_t	*setup_room(t_room **dest)
{
	t_room	*room;

	room = (t_room *)malloc(sizeof(t_room));
	if (room == NULL)
		return (EXIT_FAILURE);
	room->name = NULL;
	room->xpos = -1;
	room->ypos = -1;
	room->links = NULL;
	room->ant = -1;
	*dest = room;
	return (EXIT_SUCCESS);
}

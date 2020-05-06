/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_rooms.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 14:43:43 by kim           #+#    #+#                 */
/*   Updated: 2020/05/06 15:13:57 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

ssize_t	parse_rooms(t_input_reader *input, t_map *map, size_t *i)
{
	if (input != NULL && map != NULL)
	{
		while (i < input->num_lines && input->lines[*i] != NULL)
		{
			if (is_room(input->lines[*i]) == 1)
				if (add_room(input->lines[*i]) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			else if (is_comment(input->lines[*i] == 2))
				if (add_start(input, map, i)
		}
	}
	return (EXIT_FAILURE);
}
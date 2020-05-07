/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 14:06:39 by kim           #+#    #+#                 */
/*   Updated: 2020/05/07 14:46:55 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

ssize_t	parse_input(t_map *map, t_input_reader *input)
{
	size_t	i;

	i = 0;
	if (input != NULL && map != NULL)
	{
		if (parse_antmount(input, map, &i) == EXIT_SUCCESS &&
			parse_rooms(input, map, &i) == EXIT_SUCCESS &&
			parse_tubes(input, map, &i) == EXIT_SUCCESS)//add later: check error-meuk zoals heeft startroom links
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

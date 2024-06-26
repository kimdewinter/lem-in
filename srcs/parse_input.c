/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 14:06:39 by kim           #+#    #+#                 */
/*   Updated: 2020/09/30 13:57:29 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t	parse_input(t_map *map, t_input_reader *input)
{
	size_t	i;

	i = 0;
	if (input != NULL && map != NULL)
	{
		if (parse_antmount(input, map, &i) == EXIT_SUCCESS &&
			parse_rooms(input, map, &i) == EXIT_SUCCESS &&
			parse_tubes(input, map, &i) == EXIT_SUCCESS)
		{
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

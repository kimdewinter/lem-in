/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 14:06:39 by kim           #+#    #+#                 */
/*   Updated: 2020/07/03 16:09:11 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void		delete_input(t_input_reader *input)
{
	size_t	i;

	i = 0;
	if (input != NULL && input->lines != NULL)
	{
		while (i < input->num_lines)
		{
			if (input->lines[i] != NULL)
			{
				free(input->lines[i]);
				input->lines[i] = NULL;
			}
			i++;
		}
		free(input->lines);
		input->lines = NULL;
	}
}

ssize_t	parse_input(t_map *map, t_input_reader *input)
{
	size_t	i;

	i = 0;
	if (input != NULL && map != NULL)
	{
		if (parse_antmount(input, map, &i) == EXIT_SUCCESS &&
			parse_rooms(input, map, &i) == EXIT_SUCCESS &&
			parse_tubes(input, map, &i) == EXIT_SUCCESS &&
			sanitize_input(map) == EXIT_SUCCESS)
		{
			delete_input(input);
			return (EXIT_SUCCESS);
		}
	}
	delete_input(input);
	return (EXIT_FAILURE);
}

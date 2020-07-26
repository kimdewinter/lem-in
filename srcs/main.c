/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 14:06:51 by kim           #+#    #+#                 */
/*   Updated: 2020/07/15 15:59:57 by kim           ########   odam.nl         */
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
		if (input->lines != NULL)
			free(input->lines);
		input->lines = NULL;
	}
}

static ssize_t	setup_map(t_map *map)
{
	if (map != NULL)
	{
		map->antmount = -1;
		map->start = NULL;
		map->end = NULL;
		map->rooms = create_ht(50);
		if (map->rooms != NULL)
			return (EXIT_SUCCESS);
		map->routes = NULL;
		map->num_routes = 0;
		map->solution.len = 0;
		map->solution.combi = NULL;
		map->solution.used = 0;
		map->solution.turns = 0;
	}
	return (EXIT_FAILURE);
}

int				main(void)
{
	t_input_reader	input;
	t_map			map;

	if (setup_map(&map) == EXIT_SUCCESS &&
		read_input(&input) == EXIT_SUCCESS &&
		parse_input(&map, &input) == EXIT_SUCCESS &&
		find_routes(&map) == EXIT_SUCCESS &&
		parallelize(&map) == EXIT_SUCCESS &&
		output_result(&input, &map) == EXIT_SUCCESS)
	{
		delete_input(&input);
		delete_map(&map);
		return (EXIT_SUCCESS);
	}
	delete_input(&input);
	delete_map(&map);
	return (EXIT_FAILURE);
}

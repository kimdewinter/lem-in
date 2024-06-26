/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 14:06:51 by kim           #+#    #+#                 */
/*   Updated: 2020/10/01 14:59:59 by simoncleerd   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			delete_input(t_input_reader *input)
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
		map->solution.len = 0;
		map->solution.combi = NULL;
		map->solution.in_paths = NULL;
		map->solution.used = 0;
		map->solution.turns = 0;
		map->rooms = create_ht(50);
		if (map->rooms != NULL)
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static ssize_t	execute_algorithm(t_map *map, const t_input_reader *input)
{
	if (start_dir_conn_to_end(map) == 1)
		return (output_dir_conn(map, input));
	else
	{
		if (find_routes(map) == EXIT_SUCCESS &&
			output_result(input, map) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int				main(void)
{
	t_input_reader	input;
	t_map			map;

	if (setup_map(&map) == EXIT_FAILURE)
		return (main_error(1));
	if (read_input(&input) == EXIT_SUCCESS &&
		parse_input(&map, &input) == EXIT_SUCCESS &&
		sanitize_input(&map) == EXIT_SUCCESS &&
		execute_algorithm(&map, &input) == EXIT_SUCCESS)
	{
		delete_input(&input);
		delete_map(&map);
		return (EXIT_SUCCESS);
	}
	delete_input(&input);
	delete_map(&map);
	return (EXIT_FAILURE);
}

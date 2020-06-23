/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 14:06:51 by kim           #+#    #+#                 */
/*   Updated: 2020/05/06 14:06:51 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

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

int main(void)
{
	t_input_reader	input;
	t_map	map;

	if (setup_map(&map) == EXIT_SUCCESS &&
		read_input(&input) == EXIT_SUCCESS &&
		parse_input(&map, &input) == EXIT_SUCCESS &&
		find_routes(&map) == EXIT_SUCCESS &&
		parallelize(&map) == EXIT_SUCCESS &&
		output_result(&input, &map) == EXIT_SUCCESS)
		{
			return (EXIT_SUCCESS);
		}
	return (EXIT_FAILURE);
}

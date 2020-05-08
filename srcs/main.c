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
		map->routes = NULL;
		map->rooms = create_ht(50);
		if (map->rooms != NULL)
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int main(void)
{
	t_map	map;
	t_input_reader	input;

	if (setup_map(&map) == EXIT_SUCCESS
		&& read_input(&input) == EXIT_SUCCESS
		&& parse_input(&map, &input) == EXIT_SUCCESS)
		{
			debug(&map);
			return (EXIT_SUCCESS);
		}
	return (EXIT_FAILURE);
}

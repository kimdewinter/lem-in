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

/*ssize_t	*setup_room(t_room *dest)
{
	
	return (EXIT_SUCCESS);
}

ssize_t	setup_map(t_map *dest)
{
	t_map	map;

	map.antmount = 0;
	if (setup_room(&map.start) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}*/

int main(void)
{
	t_map	map;
	t_input_reader	input;

	// map.antmount = -1;
	// map.start = NULL;
	//map.routes = iets;
	if (read_input(&input) == EXIT_SUCCESS
		&& parse_input(&map, &input) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

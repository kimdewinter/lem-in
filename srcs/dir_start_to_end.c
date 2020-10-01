/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dir_start_to_end.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 13:54:03 by kde-wint      #+#    #+#                 */
/*   Updated: 2020/10/01 14:19:28 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

size_t	start_dir_conn_to_end(const t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->start->neighbours_len)
	{
		if (map->start->neighbours[i] == map->end)
			return (1);
		i++;
	}
	return (0);
}

ssize_t	output_dir_conn(const t_map *map, const t_input_reader *input)
{
	ssize_t	ant_counter;

	print_input(input);
	ant_counter = 1;
	while (ant_counter <= map->antmount)
	{
		ft_printf("L%i-%s", ant_counter, map->end->name);
		if (ant_counter < map->antmount)
			ft_putchar(' ');
		ant_counter++;
	}
	ft_putchar('\n');
	return (EXIT_SUCCESS);
}

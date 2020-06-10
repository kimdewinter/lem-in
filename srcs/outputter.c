/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   outputter.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 13:54:50 by kim           #+#    #+#                 */
/*   Updated: 2020/06/10 14:23:04 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void		print_input(t_input_reader *input)
{
	size_t	i;

	i = 0;
	while (i < input->num_lines)
	{
		ft_printf("%s\n", input->lines[i]);
		i++;
	}
	ft_printf("\n");
}

void		output_result(t_input_reader *input, t_map *map)
{
	(void)input;
	calculate_ants_per_path(map->antmount, &map->solution);
	// print_solution(map);
	// printf("OUTPUT:\n");
	print_input(input);
}
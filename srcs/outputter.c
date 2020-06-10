/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   outputter.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 13:54:50 by kim           #+#    #+#                 */
/*   Updated: 2020/06/10 12:59:31 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void		output_result(t_input_reader *input, t_map *map)
{
	if (input)
		calculate_ants_per_path(map->antmount, &map->solution);
	print_solution(map);
}
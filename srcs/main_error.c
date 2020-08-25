/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 15:00:39 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/25 15:16:32 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t			main_error(size_t err_code)
{
	if (err_code == 1)
		ft_printf("Error: setup_map\nError allocating memory\n");
	else if (err_code == 2)
		ft_printf("Error: setup_input\nError allocating memory\n");
	else if (err_code == 3)
		ft_printf("Error: copy_input\nError reading input\n");
	else if (err_code == 4)
		ft_printf("Error: copy_input\nError reallocating memory\n");
	// else if (err_code == 5)
	// 	ft_printf("Error: parse_tubes\nError allocating memory\n");
	// else if (err_code == 6)
	// 	ft_printf("Error: parse_tubes\nError linking rooms\n");
	// else if (err_code == 7)
	// 	ft_printf("Error: parse_tubes\nNo links between rooms detected\n");
	// else if (err_code == 8)
	// 	ft_printf("Error: sanitize input\nNo rooms provided\n");
	// else if (err_code == 9)
	// 	ft_printf("Error: sanitize input\nNo start room provided\n");
	return (EXIT_FAILURE);
}
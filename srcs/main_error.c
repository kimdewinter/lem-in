/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 15:00:39 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/25 16:23:45 by kim           ########   odam.nl         */
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
	return (EXIT_FAILURE);
}

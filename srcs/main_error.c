/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 15:00:39 by lravier       #+#    #+#                 */
/*   Updated: 2020/09/30 16:49:56 by simoncleerd   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t			main_error(size_t err_code)
{
	if (err_code == 1)
		ft_dprintf(STDERR_FILENO, \
		"Error: setup_map\nError allocating memory\n");
	else if (err_code == 2)
		ft_dprintf(STDERR_FILENO, \
		"Error: setup_input\nError allocating memory\n");
	else if (err_code == 3)
		ft_dprintf(STDERR_FILENO, \
		"Error: copy_input\nError reading input\n");
	else if (err_code == 4)
		ft_dprintf(STDERR_FILENO, \
		"Error: copy_input\nError reallocating memory\n");
	else if (err_code == 5)
		ft_dprintf(STDERR_FILENO, \
		"Error: copy_input\nEmpty file\n");
	return (EXIT_FAILURE);
}

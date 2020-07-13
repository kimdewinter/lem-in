/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   route_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 15:58:16 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/13 13:12:56 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t	route_error(size_t err_code)
{
	if (err_code == 1)
		ft_printf("Error: route_finder\nNo path from start to end found\n");
	return (EXIT_FAILURE);
}

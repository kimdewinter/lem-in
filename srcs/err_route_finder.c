/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   err_route_finder.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 14:15:58 by kim           #+#    #+#                 */
/*   Updated: 2020/07/23 14:16:57 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t		handle_err_route_finder(size_t err_code, const char *line)
{
	if (err_code == 0)
		perror("Error: unspecified error in route_finder.c\n");
	else if (err_code == 1)
		perror("Error: misallocation in route_finder.c function ");
	if (line != NULL)
		perror(line);
	return (EXIT_FAILURE);
}

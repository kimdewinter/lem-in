/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   err_route_finder.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 14:15:58 by kim           #+#    #+#                 */
/*   Updated: 2020/08/14 19:52:24 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t		handle_err_route_finder(size_t err_code, const char *line)
{
	if (err_code == 0)
		perror("Error: unspecified error in routefinder\n");
	else if (err_code == 1)
		perror("Error: misallocation in routefinder-related function ");
	else if (err_code == 2)
		perror("Error: no valid route from start to end found\n");
	else if (err_code == 3)
		perror("Error: no room remaining in t_room array wrap->route->route\n");
	else if (err_code == 4)
		perror("Error: no room remaining in t_best candidate\n");
	if (line != NULL)
		perror(line);
	return (EXIT_FAILURE);
}

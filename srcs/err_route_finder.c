/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   err_route_finder.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 14:15:58 by kim           #+#    #+#                 */
/*   Updated: 2020/08/04 18:10:02 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t		handle_err_route_finder(size_t err_code, const char *line)
{
	if (err_code == 0)
		perror("Error: unspecified error in routefinder\n");
	else if (err_code == 1)
		perror("Error: misallocation in routefinder-related function ");
	if (line != NULL)
		perror(line);
	return (EXIT_FAILURE);
}

void		handle_err_allocopy_single_route(t_route **dst)
{
	if (*dst == NULL)
	{
			if ((*dst)->bitroute != NULL)
				free((*dst)->bitroute);
			if ((*dst)->route != NULL)
				free((*dst)->route);
			free(*dst);
			*dst = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   err_route_finder.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 14:15:58 by kim           #+#    #+#                 */
/*   Updated: 2020/08/06 17:29:08 by kim           ########   odam.nl         */
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

void		handle_err_branch_or_new(t_route **dst)
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

ssize_t		handle_err_find_shortest_dist_option(t_shortest_dist *to_free)
{
	free(to_free->nb_visited);
	to_free->nb_visited = NULL;
	return (EXIT_FAILURE);
}
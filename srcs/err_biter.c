/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   err_biter.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 14:36:24 by kim           #+#    #+#                 */
/*   Updated: 2020/06/23 19:21:07 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t		handle_err_biter(size_t err_code, const char *line)
{
	if (err_code == 0)
		perror("Error: unspecified error in biter.c\n");
	else if (err_code == 1)
		perror("Error: misallocation in biter.c function ");
	if (line != NULL)
		perror(line);
	return (EXIT_FAILURE);
}

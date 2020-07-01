/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   err_paracom.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 14:36:24 by kim           #+#    #+#                 */
/*   Updated: 2020/07/01 13:24:52 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t		handle_err_para(size_t err_code, const char *line)
{
	if (err_code == 0)
		perror("Error: unspecified error in parallelizer.c function ");
	else if (err_code == 1)
		perror("Error: misallocation in parallelizer.c function ");
	else if (err_code == 2)
		perror("Erorr: parallelizer.c function parallelize received a\
				NULL-pointer to map\n");
	if (line != NULL)
		perror(line);
	return (EXIT_FAILURE);
}

ssize_t		handle_err_comtron(size_t err_code, const char *line)
{
	if (err_code == 0)
		perror("Error: unspecified error in combinatron.c\n");
	else if (err_code == 1)
		perror("Error: misallocation in combinatron.c function ");
	else if (err_code == 2)
		perror("Error: out of array scope in combinatron.c function ");
	if (line != NULL)
		perror(line);
	return (EXIT_FAILURE);
}

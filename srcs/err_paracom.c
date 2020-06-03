/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   err_paracom.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 14:36:24 by kim           #+#    #+#                 */
/*   Updated: 2020/06/03 15:05:18 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

ssize_t		handle_err_para(size_t err_code, const char *line)
{
	if (err_code == 0)
		perror("Error: unspecified error in parallelizer.c\n");
	else if (err_code == 1)
		perror("Erorr: parallelize received a NULL-pointer to map\n");
	if (line != NULL)
		perror(line);
	return (EXIT_FAILURE);
}

ssize_t		handle_err_comtron(size_t err_code, const char *line)
{
	if (err_code == 0)
		perror("Error: unspecified error in combinatron.c\n");
	if (line != NULL)
		perror(line);
	return (EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 19:01:29 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/04 19:12:57 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

size_t	parse_error(size_t err_code)
{
	if (err_code == 1)
		perror("Number of ants too large to be represented in memory\n");
	else if (err_code == 2)
		perror("Number of ants is zero\n");
	else if (err_code == 3)
		perror("No number of ants specified in input\n");
	else if (err_code == 4)
		perror("Invalid number of dashes in link line\n");
	else if (err_code == 5)
		perror("Error allocating memory\n");
	else if (err_code == 6)
		perror("Error linking rooms\n");
	else if (err_code == 7)
		perror("No links between rooms detected\n");
	return (EXIT_FAILURE);
}
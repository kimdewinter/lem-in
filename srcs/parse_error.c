/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 19:01:29 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/02 15:48:38 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t	parse_error(size_t err_code)
{
	printf("PARSE ERROR %lu\n", err_code);
	if (err_code == 1)
		ft_printf("Error: parse_antmount\nNumber of ants too large to be\
			represented in memory\n");
	else if (err_code == 2)
		ft_printf("Error: parse_antmount\nNumber of ants is zero\n");
	else if (err_code == 3)
		ft_printf("Error: parse_antmount\nNo number of ants specified in\
			input\n");
	else if (err_code == 4)
		ft_printf("Error: parse_tubes\nInvalid number of dashes in link\
			line\n");
	else if (err_code == 5)
		ft_printf("Error: parse_tubes\nError allocating memory\n");
	else if (err_code == 6)
		ft_printf("Error: parse_tubes\nError linking rooms\n");
	else if (err_code == 7)
		ft_printf("Error: parse_tubes\nNo links between rooms detected\n");
	else if (err_code == 8)
		ft_printf("Error: sanitize input\nNo rooms provided\n");
	else if (err_code == 9)
		ft_printf("Error: sanitize input\nNo start room provided\n");
	else if (err_code == 10)
		ft_printf("Error: sanitize input\nNo end room provided\n");
	else if (err_code == 11)
		ft_printf("Error: sanitize input\nNo path from start room\n");
	else if (err_code == 12)
		ft_printf("Error: sanitize input\nNo path from end room\n");
	else if (err_code == 13)
		ft_printf("Error: parse_rooms\nNo links between rooms specified\n");
	else if (err_code == 14)
		ft_printf("Error: parse_rooms\nError allocating memory for bitconj\n");
	else if (err_code == 15)
		ft_printf("Error: parse_tubes\nConnection between rooms specified\
			twice\n");
	return (EXIT_FAILURE);
}

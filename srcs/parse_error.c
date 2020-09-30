/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 19:01:29 by lravier       #+#    #+#                 */
/*   Updated: 2020/09/30 14:03:32 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	parse_error_cont(size_t err_code)
{
	if (err_code == 10)
		ft_dprintf(STDERR_FILENO, "Error: sanitize input\nNo end room \
provided\n");
	else if (err_code == 11)
		ft_dprintf(STDERR_FILENO, "Error: sanitize input\nNo path from \
start room\n");
	else if (err_code == 12)
		ft_dprintf(STDERR_FILENO, "Error: sanitize input\nNo path from \
end room\n");
	else if (err_code == 13)
		ft_dprintf(STDERR_FILENO, "Error: parse_rooms\nNo links between rooms \
specified\n");
	else if (err_code == 14)
		ft_dprintf(STDERR_FILENO, "Error: parse_rooms\nError allocating memory \
for bitconj\n");
	else if (err_code == 15)
		ft_dprintf(STDERR_FILENO, "Error: parse_tubes\nConnection between \
rooms specified twice\n");
	else if (err_code == 16)
		ft_dprintf(STDERR_FILENO, "Error: parse_rooms\nCoordinate specified \
too large to be represented in integer\n");
	else if (err_code == 17)
		ft_dprintf(STDERR_FILENO, "Error: parse_rooms\nInvalid line found\n");
	else if (err_code == 18)
		ft_dprintf(STDERR_FILENO, "Error: parse_rooms\nDuplicate room names\n");
	else if (err_code == 19)
		ft_dprintf(STDERR_FILENO, "Error: parse_tubes\nRoom specified in link \
doesn't exist\n");
	else if (err_code == 20)
		ft_dprintf(STDERR_FILENO, "Error: parse_rooms_add_room\nLine after \
start or end comment does not specify valid room\n");
	return (EXIT_FAILURE);
}

ssize_t			parse_error(size_t err_code)
{
	if (err_code == 0)
		ft_dprintf(STDERR_FILENO, "Error: allocation error\n");
	if (err_code == 1)
		ft_dprintf(STDERR_FILENO, "Error: parse_antmount\nNumber of ants too \
large to be represented in memory\n");
	else if (err_code == 2)
		ft_dprintf(STDERR_FILENO, "Error: parse_antmount\nNumber of ants is \
zero\n");
	else if (err_code == 3)
		ft_dprintf(STDERR_FILENO, "Error: parse_antmount\nNo number of ants \
specified in input\n");
	else if (err_code == 4)
		ft_dprintf(STDERR_FILENO, "Error: parse_tubes\nInvalid number of \
dashes in link line\n");
	else if (err_code == 5)
		ft_dprintf(STDERR_FILENO, "Error: parse_tubes\nError allocating \
memory\n");
	else if (err_code == 6)
		ft_dprintf(STDERR_FILENO, "Error: parse_tubes\nError linking rooms\n");
	else if (err_code == 7)
		ft_dprintf(STDERR_FILENO, "Error: parse_tubes\nNo links between rooms \
detected\n");
	else if (err_code == 8)
		ft_dprintf(STDERR_FILENO, "Error: sanitize input\nNo rooms provided\n");
	else if (err_code == 9)
		ft_dprintf(STDERR_FILENO, "Error: sanitize input\nNo start room \
provided\n");
	return (parse_error_cont(err_code));
}

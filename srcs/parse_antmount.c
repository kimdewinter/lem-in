/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_antmount.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 17:39:21 by lravier       #+#    #+#                 */
/*   Updated: 2020/09/29 19:45:20 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

uint64_t			ft_atoi_ul(char *line, size_t *overflow)
{
	int			i;
	uint64_t	result;

	result = 0;
	i = 0;
	while (line[i])
	{
		if (result > UINT64_MAX / 10
		|| ((result == (UINT64_MAX / 10)) && ((line[i] - '0') > 5)))
		{
			*overflow = 1;
			return (0);
		}
		result = (result * 10) + (line[i] - '0');
		i++;
	}
	return (result);
}

ssize_t				parse_antmount(t_input_reader *input, t_map *map, size_t *i)
{
	uint64_t	antmount;
	size_t		overflow;

	while (is_comment(input->lines[*i]) == 1)
		(*i)++;
	if (is_antmount(input->lines[*i]) == 1)
	{
		overflow = 0;
		antmount = ft_atoi_ul(input->lines[*i], &overflow);
		if (overflow == 1)
			return (parse_error(1));
		if (antmount == 0)
			return (parse_error(2));
		map->antmount = antmount;
		(*i)++;
		return (EXIT_SUCCESS);
	}
	return (parse_error(3));
}

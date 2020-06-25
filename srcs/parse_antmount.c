/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_antmount.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 17:39:21 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/25 15:22:41 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

unsigned long long		ft_atoi_ll(char *line, size_t *overflow)
{
	int			i;
	long long	result;
	long long	prev_result;

	result = 0;
	i = 0;
	while (line[i])
	{
		prev_result = result;
		result = (result * 10) + (line[i] - '0');
		if ((result - (line[i] - '0')) / 10 != prev_result)
		{
			*overflow = 1;
			return (0);
		}
		i++;
	}
	return (result);
}

ssize_t		parse_antmount(t_input_reader *input, t_map *map, size_t *i)
{
	size_t	antmount;
	size_t	overflow;

	while (is_comment(input->lines[*i]) == 1)
		(*i)++;
	if (is_antmount(input->lines[*i]))
	{
		overflow = 0;
		antmount = ft_atoi_ll(input->lines[*i], &overflow);
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

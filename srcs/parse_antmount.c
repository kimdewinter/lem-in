/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_antmount.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 17:39:21 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/06 15:14:06 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

unsigned long long		ft_atoi_ll(char *line, size_t *overflow)
{
	int			i;
	int			polar;
	long long	result;
	long long	prev_result;

	result = 0;
	i = 0;
	polar = 1;
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
	size_t				antmount;
	size_t				overflow;

	/* Checks whether skippable lines */
	while (is_comment(input->lines[*i]) < 2)
		(*i)++;
	if (is_antmount(input->lines[*i]))
	{
		overflow = 0;
		antmount = ft_atoi_ll(input->lines[*i], &overflow);
		if (overflow)
			return (ft_error("Number of ants too large to be represented\n",
			EXIT_FAILURE));
		if (antmount == 0)
			return (ft_error("No ants found\n", EXIT_FAILURE));
		map->antmount = antmount;
		return (EXIT_SUCCESS);
	}
	/* Could be anything wrong */
	return (EXIT_FAILURE);
	/* What is the biggest number of ants that is still legal?? */
}

		// while (i < input->num_lines && input->lines[i] != NULL)
		// {			
		// 	if (is_antmount(input->lines[i] == 1))
		// 		parse_antmount(input->lines[i], map);
		// 	else if (is_comment(input->lines[i] == 1))
		// 		continue;
		// 	else if (map->antmount != -1)
		// 		break;
		// 	else
		// 		return (EXIT_FAILURE);
		// }
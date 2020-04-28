/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_antmount.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 17:39:21 by lravier       #+#    #+#                 */
/*   Updated: 2020/04/28 18:20:33 by kim           ########   odam.nl         */
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
	while (str[i])
	{
		prev_result = result;
		result = (result * 10) + (str[i] - '0');
		if ((result - (str[i] - '0')) / 10 != prev_result)
		{
			*overflow = 1;
			return (0);
		}
		i++;
	}
	return (result);
}

ssize_t		parse_antmount(char *line, t_map *map)
{
	size_t				antmount;
	size_t				overflow;

	overflow = 0;
	antmount = ft_atoi_ll(line, &overflow)
	if (overflow)
		return (ft_error("Number of ants too large to be represented\n", 0));
	if (antmount)
		return (ft_error("No ants detected\n", 0));
	map->antmount = antmount;
	return (1);
	/* What is the biggest number of ants that is still legal?? */
}

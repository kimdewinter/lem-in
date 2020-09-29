/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   atoi_overflow.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/29 17:18:04 by lravier       #+#    #+#                 */
/*   Updated: 2020/09/29 19:39:43 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int	check_overflow(char c, int result,
int *overflow, int polar)
{
	if (result > INT_MAX / 10
	|| (result == INT_MAX / 10 &&
	(((c - '0') > 7 && polar == 1)
	|| ((c - '0' > 8 && polar == -1)))))
	{
		*overflow = 1;
		return (1);
	}
	return (0);
}

int			atoi_overflow(char *str, int *overflow)
{
	int	i;
	int	polar;
	int	result;

	result = 0;
	i = 0;
	polar = 1;
	if (str[i] == '-' && ft_isdigit(str[i + 1]))
	{
		if (str[i] == '-')
		{
			polar = -1;
			i++;
		}
	}
	while (ft_isdigit(str[i]) == 1)
	{
		if (check_overflow(str[i], result, overflow, polar) == 1)
			return (0);
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * polar);
}

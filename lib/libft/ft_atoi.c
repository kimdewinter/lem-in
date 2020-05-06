/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/20 15:55:36 by lravier        #+#    #+#                */
/*   Updated: 2019/10/15 18:28:51 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int	i;
	int	polar;
	int	result;

	result = 0;
	i = 0;
	polar = 1;
	while (ft_isspace(str[i]))
		i++;
	if ((str[i] == '+' || str[i] == '-') && ft_isdigit(str[i + 1]))
	{
		if (str[i] == '-')
			polar = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * polar);
}

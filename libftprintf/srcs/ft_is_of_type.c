/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_of_type.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 13:25:37 by lravier        #+#    #+#                */
/*   Updated: 2019/10/13 20:24:03 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

int		is_number(char c)
{
	if (c >= '1' && c <= '9')
		return (1);
	return (0);
}

int		is_flag(char c)
{
	if (c == '#' || c == '0' || c == '-' || c == ' ' || c == '+')
		return (1);
	return (0);
}

int		is_conversion(char c)
{
	if (c == 'd' || c == 'i' || c == 'o' || c == 'x' || c == 'X' ||
	c == 'e' || c == 'E' || c == 'f' || c == 'F' || c == 'g' || c == 'G'
	|| c == 'c' || c == 's' || c == 'p' || c == 'u' || c == 'b')
		return (1);
	return (0);
}

int		is_lm(char c)
{
	if (c == 'h' || c == 'l' || c == 'L')
		return (1);
	return (0);
}

int		is_valid(char c)
{
	if (is_flag(c) || is_number(c) || is_lm(c) || c == '*' || c == '.')
		return (1);
	return (0);
}

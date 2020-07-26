/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_conversion_type.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/07 11:29:35 by lravier        #+#    #+#                */
/*   Updated: 2019/11/08 10:21:37 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

int		has_alt_form(char c)
{
	if (c == 'o' || c == 'x' || c == 'X' || c == 'e' || c == 'E' || c == 'f' ||
	c == 'F' || c == 'g' || c == 'G' || c == 'p')
		return (1);
	return (0);
}

int		is_numeric_conversion(char c)
{
	if (c == 'd' || c == 'i' || c == 'o' || c == 'u' || c == 'x' || c == 'X'
	|| c == 'e' || c == 'E' || c == 'f' || c == 'F' || c == 'g' || c == 'G' ||
	c == 'p')
		return (1);
	return (0);
}

int		is_signed_conversion(char c)
{
	if (c == 'd' || c == 'i' || c == 'e' || c == 'E' || c == 'f' || c == 'F' ||
	c == 'g' || c == 'G')
		return (1);
	return (0);
}

int		is_dioux(char c)
{
	if (c == 'd' || c == 'i' || c == 'o' || c == 'u' || c == 'x' || c == 'X')
		return (1);
	return (0);
}

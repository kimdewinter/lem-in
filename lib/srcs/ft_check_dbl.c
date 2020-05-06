/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_check_dbl.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 13:32:00 by lravier        #+#    #+#                */
/*   Updated: 2019/11/14 13:33:31 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

void			check_double(int dbl, va_list args)
{
	if (dbl == 0)
		va_arg(args, void *);
}

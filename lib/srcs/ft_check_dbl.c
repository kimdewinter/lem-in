/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_check_dbl.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 13:32:00 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/25 17:11:20 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

void			check_double(int dbl, va_list args)
{
	if (dbl == 0)
		va_arg(args, void *);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_empty.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 13:07:50 by lravier        #+#    #+#                */
/*   Updated: 2019/11/11 12:01:42 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

int		ft_handle_empty(t_pf_arg *instr, const char *format)
{
	int len;

	len = 0;
	if (format[instr->end_ind] != '\0')
		len++;
	if (len != 0)
	{
		instr->tmp = ft_strnew(len);
		if (!instr->tmp)
			return (0);
	}
	if (format[instr->end_ind] != '\0')
		instr->tmp[0] = format[instr->end_ind];
	instr->len = len;
	return (1);
}

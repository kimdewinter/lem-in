/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_len_zero_excep.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 16:20:02 by lravier        #+#    #+#                */
/*   Updated: 2019/11/08 13:15:06 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"
#include "../libft/libft.h"

int		get_len_zero_excep(t_pf_arg *instr, int len, t_bigint *val)
{
	int res;

	res = len;
	if (len == 1 && (instr->conversion == 'e' || instr->conversion == 'E'))
		res += 4;
	if (instr->flags[0] == 1 && len == 1 && instr->precision == 0)
		res++;
	if ((instr->flags[3] == 1 || instr->flags[4] == 1) && val->sign == 0)
		res++;
	if (val->sign == 1)
		res++;
	if (len == 1)
	{
		if (instr->precision != 0 && (instr->conversion != 'g' &&
		instr->conversion != 'G'))
			res++;
		res += instr->precision;
	}
	return (res);
}

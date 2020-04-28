/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_length.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 13:58:10 by lravier        #+#    #+#                */
/*   Updated: 2019/10/30 14:01:31 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"
#include "../libft/libft.h"

static int		get_len_dec(t_bigint val)
{
	int			i;
	uint32_t	len;
	int			state;
	uint32_t	factor;
	uint32_t	fract;

	if (val.startind == -1 && val.biggest_exp == -1)
		return (0);
	i = val.startind;
	len = 0;
	state = 0;
	factor = BASE;
	while (factor)
	{
		fract = val.big[i] / factor;
		if (fract)
			state = 1;
		if (state)
		{
			len++;
			val.big[i] -= fract * factor;
		}
		factor /= 10;
	}
	return (len + ((val.biggest_exp - 1 - i) * DECPLB));
}

void			ft_get_len_f(t_pf_arg *instr, t_bigint *val)
{
	instr->len = get_len_dec(*val);
	if (instr->len == 0)
		instr->len++;
	if (instr->precision == 0)
	{
		if (instr->flags[0] == 1)
			instr->len++;
	}
	else
		instr->len++;
	if (val->sign == 1)
		instr->len++;
	else
	{
		if (instr->flags[3] == 1 || instr->flags[4] == 1)
			instr->len++;
	}
	instr->len += instr->precision;
}

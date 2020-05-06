/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_zero_str.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 14:22:37 by lravier        #+#    #+#                */
/*   Updated: 2019/11/09 14:40:27 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"
#include "../libft/libft.h"

static void			ft_zero_e(t_pf_arg *instr, int i)
{
	int j;

	j = 0;
	while (j < instr->precision)
	{
		i++;
		j++;
	}
	if (instr->conversion == 'e')
		instr->tmp[i] = 'e';
	else
		instr->tmp[i] = 'E';
	i++;
	instr->tmp[i] = '+';
}

static void			ft_floats(t_pf_arg *instr, int i)
{
	if (instr->conversion == 'f' || instr->conversion == 'F')
	{
		if (i < instr->len)
		{
			instr->tmp[i] = '.';
			i++;
		}
	}
	if (instr->conversion == 'g' || instr->conversion == 'G')
	{
		if (instr->flags[0] == 1 || instr->precision - 1 > 0)
		{
			instr->tmp[i] = '.';
			i++;
		}
	}
	else if (instr->conversion == 'e' || instr->conversion == 'E')
	{
		if (instr->flags[0] == 1 || instr->precision > 0)
		{
			instr->tmp[i] = '.';
			i++;
		}
		ft_zero_e(instr, i);
	}
}

int					ft_zero_string(t_pf_arg *instr, t_bigint *val)
{
	int i;

	i = 0;
	instr->len = get_len_zero_excep(instr, 1, val);
	instr->tmp = ft_strnew(instr->len);
	if (!instr->tmp)
		return (0);
	ft_memset(instr->tmp, '0', instr->len);
	if ((instr->flags[3] == 1 || instr->flags[4] == 1) && val->sign == 0)
	{
		if (instr->flags[3] == 1)
			instr->tmp[i] = ' ';
		else
			instr->tmp[i] = '+';
		i++;
	}
	if (val->sign == 1)
	{
		instr->tmp[i] = '-';
		i++;
	}
	i++;
	ft_floats(instr, i);
	free(val);
	return (1);
}

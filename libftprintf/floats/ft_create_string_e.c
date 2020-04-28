/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_create_string_e.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 15:17:16 by lravier        #+#    #+#                */
/*   Updated: 2019/11/09 16:48:32 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"
#include "../libft/libft.h"

static void		ft_get_len(t_pf_arg *instr, t_bigint *val, int fact)
{
	instr->len = 1;
	if (val->sign == 1)
		instr->len++;
	else
	{
		if (instr->flags[3] == 1 || instr->flags[4] == 1)
			instr->len++;
	}
	if (instr->precision == 0)
	{
		if (instr->flags[0] == 1)
			instr->len++;
	}
	else
	{
		instr->len++;
		instr->len += instr->precision;
	}
	instr->len += 2;
	instr->len += ft_add_len_fact(fact);
}

static void		set_exp(int *i, t_pf_arg *instr, t_bigint *val)
{
	if (val->sign == 1)
	{
		instr->tmp[*i] = '-';
		(*i)++;
	}
	else
	{
		if (instr->flags[3] == 1)
		{
			instr->tmp[*i] = ' ';
			(*i)++;
		}
		if (instr->flags[4] == 1)
		{
			instr->tmp[*i] = '+';
			(*i)++;
		}
	}
}

void			ft_fill_fract(t_pf_arg *instr, t_bigint *val, int *mult, int *i)
{
	int j;
	int k;
	int l;
	int tmp;

	j = val->startind;
	k = 0;
	l = *i;
	while (k < instr->precision && j < 128)
	{
		while (*mult && k < instr->precision && j < 128)
		{
			tmp = (val->big[j] % (10 * *mult)) / *mult;
			instr->tmp[l] = tmp + '0';
			*mult /= 10;
			k++;
			l++;
		}
		*mult = BASE / 10;
		j++;
	}
	*i += instr->precision;
}

static void		ft_fill_string_e(t_pf_arg *instr, t_bigint *val, int mult,
int fact)
{
	int i;
	int j;

	i = 0;
	j = val->startind;
	if (j == -1)
		j = 0;
	set_exp(&i, instr, val);
	instr->tmp[i] = (val->big[j] / mult) + '0';
	i++;
	mult /= 10;
	if (instr->flags[0] == 1 || instr->precision != 0)
	{
		instr->tmp[i] = '.';
		i++;
	}
	ft_fill_fract(instr, val, &mult, &i);
	ft_add_exp(instr, fact, i);
}

int				ft_create_string_e(t_pf_arg *instr, t_bigint *val, int mult,
int fact)
{
	ft_get_len(instr, val, fact);
	instr->tmp = ft_strnew(instr->len);
	if (!instr->tmp)
		return (0);
	ft_memset(instr->tmp, '0', instr->len);
	ft_fill_string_e(instr, val, mult, fact);
	free(val);
	return (1);
}

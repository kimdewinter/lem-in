/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_string_exceptions.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 14:10:10 by lravier        #+#    #+#                */
/*   Updated: 2019/11/08 13:05:41 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"
#include "../libft/libft.h"

static void		ft_set_prefix(t_pf_arg *instr, int *i, t_bigint *val)
{
	if ((instr->flags[3] == 1 || instr->flags[4] == 1) && val->sign == 0)
	{
		if (instr->flags[3] == 1)
			instr->tmp[*i] = ' ';
		else
			instr->tmp[*i] = '+';
		(*i)++;
	}
	if (val->sign == 1)
	{
		instr->tmp[*i] = '-';
		(*i)++;
	}
}

int				ft_string_exceptions(long double num, t_pf_arg *instr,
t_bigint *val)
{
	int i;

	i = 0;
	instr->flags[1] = 0;
	instr->len = get_len_zero_excep(instr, 3, val);
	instr->tmp = ft_strnew(instr->len);
	if (!instr->tmp)
		return (0);
	ft_set_prefix(instr, &i, val);
	if (ft_isnan(num))
		ft_strcpy(&instr->tmp[i], "nan");
	else
		ft_strcpy(&instr->tmp[i], "inf");
	if (instr->conversion == 'F' || instr->conversion == 'E')
		ft_strtoupper(instr->tmp);
	free(val);
	return (1);
}

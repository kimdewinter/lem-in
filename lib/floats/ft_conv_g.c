/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_conv_g.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 15:14:03 by lravier        #+#    #+#                */
/*   Updated: 2019/11/14 13:14:21 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"
#include "../libft/libft.h"

static int	ft_remove_trailing_e(t_pf_arg *instr)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = instr->tmp;
	i = instr->len - 1;
	j = instr->len - 1;
	while (instr->tmp[j] != 'e' && instr->tmp[j] != 'E')
		j--;
	i = j - 1;
	while (instr->tmp[i] == '0')
		i--;
	instr->len = instr->len - (j - i) + 1;
	if (instr->tmp[i] == '.' && instr->flags[0] == 0)
	{
		instr->len--;
		i--;
	}
	instr->tmp = ft_strnew(instr->len);
	if (!instr->tmp)
		return (0);
	ft_strncpy(instr->tmp, tmp, i + 1);
	ft_strcpy(&instr->tmp[i + 1], &tmp[j]);
	free(tmp);
	return (1);
}

static int	ft_remove_trailing_f(t_pf_arg *instr)
{
	int		j;
	char	*tmp;

	tmp = instr->tmp;
	j = instr->len - 1;
	while (instr->tmp[j] == '0')
		j--;
	if (instr->tmp[j] == '.' && instr->flags[0] == 0)
		j--;
	instr->len = j + 1;
	instr->tmp = ft_strnew(instr->len);
	if (!instr->tmp)
		return (0);
	ft_strncpy(instr->tmp, tmp, instr->len);
	free(tmp);
	return (1);
}

static int	ft_g_as_e(t_pf_arg *instr, t_bigint *val, long int exp)
{
	int fact;
	int mult;

	instr->precision--;
	fact = 0;
	mult = ft_scale_bigint(val, instr, &fact, exp);
	if (!ft_create_string_e(instr, val, mult, fact))
		return (0);
	if (instr->flags[0] == 0)
	{
		if (!ft_remove_trailing_e(instr))
			return (0);
	}
	return (1);
}

static int	ft_g_as_f(t_pf_arg *instr, t_bigint *val)
{
	ft_adjust_precision(instr, val);
	ft_round_bigint(val, instr->precision, instr);
	if (!ft_create_string(instr, val))
		return (0);
	if (instr->flags[0] == 0)
	{
		if (!ft_remove_trailing_f(instr))
			return (0);
	}
	return (1);
}

int			ft_conv_g(t_pf_arg *instr, t_bigint *val, long int exp)
{
	t_pf_arg	cpy_instr;
	t_bigint	cpy_val;
	int			fact;

	fact = 0;
	cpy_val = *val;
	cpy_instr = *instr;
	ft_scale_bigint(&cpy_val, &cpy_instr, &fact, exp);
	cpy_instr.precision--;
	if (fact < -4 || fact >= instr->precision)
		return (ft_g_as_e(instr, val, exp));
	else
		return (ft_g_as_f(instr, val));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   float_utilities.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 15:10:34 by lravier        #+#    #+#                */
/*   Updated: 2019/11/09 18:29:32 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"

void			ft_get_startind(t_bigint *val)
{
	int i;

	i = 0;
	while (val->big[i] == 0 && i < ARR && i < (val->biggest_exp - 1))
		i++;
	val->startind = i;
}

int				ft_isnan(long double x)
{
	if (x != x)
		return (1);
	return (0);
}

int				ft_isinf(long double x)
{
	if (!ft_isnan(x) && ft_isnan(x - x))
		return (1);
	return (0);
}

long int		ft_abs(long int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

void			ft_adjust_precision(t_pf_arg *instr, t_bigint *val)
{
	uint32_t	mult;
	int			i;

	i = val->startind;
	mult = BASE;
	while ((val->big[i] / mult) == 0)
		mult /= 10;
	while (mult)
	{
		mult /= 10;
		instr->precision--;
	}
	i++;
	while (i < val->biggest_exp)
	{
		instr->precision -= 6;
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shift_left.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 14:11:32 by lravier        #+#    #+#                */
/*   Updated: 2019/10/30 14:12:34 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"

static void			ft_shift(t_bigint *val, int shift, uint32_t *remainder)
{
	int i;

	i = shift;
	while (i < ARR)
	{
		val->big[i - shift] = val->big[i];
		val->big[i] = 0;
		i++;
	}
	if ((i - shift) != ARR)
		val->big[i - shift] = BASE / 2;
	*remainder = 0;
}

static void			calc_shift_dec(int *i, t_bigint *val, int *shift)
{
	while (val->big[*i] == 0 && *i < val->biggest_exp)
	{
		if (val->startind == 0)
			val->startind = -1;
		else if (val->startind != -1)
			val->startind--;
		(*shift)++;
		(*i)++;
	}
}

static void			calc_shift_fract(int *i, t_bigint *val, int *shift)
{
	while (val->big[*i] == 0)
	{
		(*i)++;
		(*shift)++;
		val->zeros++;
	}
}

static void			set_biggest_exp(int *diff, t_bigint *val)
{
	if (val->startind == -1)
		val->biggest_exp = -1;
	else
		val->biggest_exp -= *diff;
}

void				shift_left(uint32_t *remainder, t_bigint *val)
{
	int shift;
	int diff;
	int i;

	i = val->startind;
	if (i == -1)
		i = 0;
	shift = 0;
	diff = val->biggest_exp - val->startind;
	calc_shift_dec(&i, val, &shift);
	i = val->biggest_exp;
	if (i == -1)
		i = 0;
	calc_shift_fract(&i, val, &shift);
	set_biggest_exp(&diff, val);
	ft_shift(val, shift, remainder);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mult_bigint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 16:26:42 by lravier        #+#    #+#                */
/*   Updated: 2019/10/30 14:05:01 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"

static void		ft_handle_carry(uint32_t *carry, int i, int *stp,
t_bigint *val)
{
	val->big[i] = *carry;
	val->biggest_exp++;
	(*stp)--;
	*carry = 0;
}

static void		ft_mult_val(t_bigint *val, uint32_t *carry, int *i, int stp)
{
	uint32_t dig;

	while (*i >= stp)
	{
		dig = (val->big[*i] * 2) + *carry;
		*carry = dig / BASE;
		val->big[*i] = dig % BASE;
		(*i)--;
	}
}

static void		ft_update_val(t_bigint *val, int *stp)
{
	val->startind = *stp;
	*stp = val->biggest_exp;
	val->biggest_exp = *stp + val->startind;
}

int				ft_mult_bigint(t_bigint *val, long int exp)
{
	int			i;
	int			j;
	int			stp;
	uint32_t	carry;

	j = 0;
	carry = 0;
	exp = ft_abs(exp);
	while (j < exp)
	{
		i = ARR - 1;
		stp = (i - val->biggest_exp) + 1;
		if (stp < 0)
			return (0);
		ft_mult_val(val, &carry, &i, stp);
		if (carry != 0)
		{
			if (i >= 0)
				ft_handle_carry(&carry, i, &stp, val);
		}
		j++;
	}
	ft_update_val(val, &stp);
	return (1);
}

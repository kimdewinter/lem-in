/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_round_bigint.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 14:05:15 by lravier        #+#    #+#                */
/*   Updated: 2019/11/09 14:38:24 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"

static uint32_t		ft_power(uint32_t n)
{
	uint32_t i;
	uint32_t pow;

	pow = 1;
	i = 0;
	while ((n / pow) >= 1 && (pow <= BASE))
	{
		pow *= 10;
		i++;
	}
	return (i);
}

static void			ft_add_bigint(t_bigint *val, uint32_t pwr,
int index, t_pf_arg *instr)
{
	uint32_t	tmp;
	int			start;

	tmp = val->big[val->startind];
	start = val->startind;
	val->big[index] += pwr;
	while ((val->big[index] / BASE != 0) && index >= 0)
	{
		val->big[index] -= BASE;
		index--;
		val->big[index] += 1;
		if (index < val->startind)
		{
			val->startind--;
			if (instr->conversion == 'g' || instr->conversion == 'G')
				instr->precision--;
		}
	}
	if (ft_power((val->big[val->startind]) > ft_power(tmp)) &&
	(instr->conversion == 'g' || instr->conversion == 'G') &&
	val->startind == start)
		instr->precision--;
}

static uint32_t		calculate_next_dig(uint32_t pwr, t_bigint *val, int index)
{
	uint32_t rst;
	uint32_t remove;
	uint32_t nxt_pos;

	rst = val->big[index] % pwr;
	nxt_pos = pwr / 10;
	if (rst < nxt_pos)
		return (0);
	else
	{
		remove = val->big[index] % nxt_pos;
		rst -= remove;
		rst /= nxt_pos;
		return (rst);
	}
}

static void			ft_round_position(int prec, int index,
t_bigint *val, t_pf_arg *instr)
{
	uint32_t pwr;
	uint32_t rest;

	pwr = BASE;
	while (prec)
	{
		pwr /= 10;
		prec--;
	}
	rest = calculate_next_dig(pwr, val, index);
	if (rest >= 5)
		ft_add_bigint(val, pwr, index, instr);
}

void				ft_round_bigint(t_bigint *val, int prec, t_pf_arg *instr)
{
	int index;

	index = val->biggest_exp;
	if (index == -1)
		index = 0;
	prec -= (6 * val->zeros);
	while (prec >= DECPLB)
	{
		prec -= DECPLB;
		index++;
	}
	if (index < ARR)
		ft_round_position(prec, index, val, instr);
}

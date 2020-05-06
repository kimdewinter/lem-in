/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_div_bigint.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 15:23:57 by lravier        #+#    #+#                */
/*   Updated: 2019/11/09 14:35:13 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"

static uint32_t		ft_fact(uint32_t num)
{
	uint32_t res;

	res = 1;
	while (num >= 10)
	{
		num /= 10;
		res *= 10;
	}
	return (res);
}

static uint32_t		ft_tail_div(uint32_t *rem, uint32_t *num, int base,
uint32_t nfact)
{
	uint32_t tmp;
	uint32_t div;
	uint32_t quotient;

	div = base * nfact;
	if (div != 0)
	{
		tmp = (*num) - ((*num) % nfact);
		quotient = tmp / div;
		*num -= quotient * div;
		*rem = tmp - (quotient * div);
		return (quotient * nfact);
	}
	else
		*rem = 0;
	return (0);
}

static uint32_t		ft_div(uint32_t num, int base, uint32_t *rem)
{
	uint32_t nfact;
	uint32_t result;

	result = 0;
	if (num == 0 && *rem == 0)
		return (0);
	nfact = ft_fact(num);
	if (*rem != 0)
	{
		result += BASE / 2;
		*rem = 0;
	}
	while (nfact != 0)
	{
		result += ft_tail_div(rem, &num, base, nfact);
		nfact /= 10;
	}
	return (result);
}

int					ft_div_bigint(t_bigint *val, long int exp)
{
	int			i;
	int			j;
	uint32_t	remainder;

	exp = ft_abs(exp);
	i = 0;
	while (i < exp)
	{
		j = 0;
		remainder = 0;
		while (j < ARR)
		{
			val->big[j] = ft_div(val->big[j], 2, &remainder);
			j++;
		}
		if (remainder && j == 128)
			shift_left(&remainder, val);
		i++;
	}
	if (val->startind != -1)
		ft_get_startind(val);
	return (1);
}

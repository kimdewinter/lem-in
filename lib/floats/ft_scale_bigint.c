/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_scale_bigint.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 15:56:46 by lravier        #+#    #+#                */
/*   Updated: 2019/11/09 14:39:07 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"
#include "../libft/libft.h"

static void		ft_scale_zu(t_bigint *val, int *fact, int *mult)
{
	int i;

	i = val->startind;
	if (val->startind == -1)
		i = 0;
	*fact = (val->biggest_exp - 1 - val->startind) * 6;
	while (val->big[i] / *mult != 0)
	{
		(*fact)++;
		*mult *= 10;
	}
	(*fact)--;
	*mult /= 10;
}

static void		ft_scale_uz(t_bigint *val, int *fact, int *mult)
{
	int i;

	i = val->startind;
	i++;
	while (val->big[i] == 0)
	{
		i++;
		*fact -= 6;
	}
	val->startind = i;
	while ((val->big[i] / *mult) == 0)
	{
		(*fact)--;
		*mult /= 10;
	}
	(*fact)--;
	*fact -= DECPLB * val->zeros;
}

int				ft_scale_bigint(t_bigint *val, t_pf_arg *instr, int *fact,
long int exp)
{
	int mult;

	exp += 63;
	if (exp >= 0)
	{
		mult = 1;
		ft_scale_zu(val, fact, &mult);
	}
	else
	{
		mult = BASE / 10;
		ft_scale_uz(val, fact, &mult);
	}
	ft_round_e(val, instr, fact, &mult);
	return (mult);
}

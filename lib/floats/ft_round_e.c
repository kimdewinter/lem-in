/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_round_e.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 14:13:03 by lravier        #+#    #+#                */
/*   Updated: 2019/10/30 14:15:12 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"
#include "../libft/libft.h"

static void		set_mult(int *mult, t_pf_arg *instr, t_bigint *val, int *i)
{
	long long int	index_max;
	int				plcs;

	plcs = 0;
	index_max = get_maxind(val, instr, *mult);
	while (plcs < index_max)
	{
		while (*mult && (plcs < index_max))
		{
			plcs++;
			*mult /= 10;
		}
		if (!*mult)
			(*i)++;
		if (plcs < index_max || !*mult)
			*mult = BASE / 10;
	}
}

static void		ft_round_pos(int *mult, t_bigint *val, int i)
{
	if (*mult)
	{
		if (((val->big[i] % (10 * *mult)) / *mult) >= 5)
			val->big[i] += (10 * (*mult));
	}
	else if (i < (ARR - 1))
	{
		if (((val->big[i + 1] % BASE) / (BASE / 10)) >= 5)
			val->big[i + 1] += (BASE / 10);
		if (val->big[i + 1] >= BASE)
		{
			val->big[i + 1] -= BASE;
			val->big[i] += 1;
		}
	}
}

static void		ft_adjust_overflow(int *i, t_bigint *val)
{
	while (val->big[*i] >= BASE)
	{
		val->big[*i] -= BASE;
		(*i)--;
		if ((*i) >= 0)
			val->big[*i] += 1;
	}
}

static void		ft_setup(int *i, t_bigint *val, int *start, int *mult)
{
	if (val->startind == -1)
	{
		(*i) = 0;
		(*start) = 0;
	}
	else
	{
		(*i) = val->startind;
		(*start) = val->startind;
	}
	(*mult) /= 10;
}

void			ft_round_e(t_bigint *val, t_pf_arg *instr, int *fact, int *mult)
{
	int i;
	int start;
	int init_mult;

	init_mult = *mult;
	ft_setup(&i, val, &start, mult);
	set_mult(mult, instr, val, &i);
	ft_round_pos(mult, val, i);
	ft_adjust_overflow(&i, val);
	if (i < start && val->startind != -1)
	{
		(*fact)++;
		val->startind--;
		init_mult = 1;
	}
	else if (val->startind != -1 && (val->big[val->startind] / init_mult >= 10))
	{
		(*fact)++;
		init_mult = val->big[i];
	}
	*mult = init_mult;
}

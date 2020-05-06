/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_string.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 16:21:33 by lravier        #+#    #+#                */
/*   Updated: 2019/11/14 13:14:45 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"
#include "../libft/libft.h"

static int		ft_scale_by_exp(long int exp, t_bigint *val)
{
	if (exp >= 0)
	{
		if (!ft_mult_bigint(val, exp))
			return (0);
	}
	else
	{
		if (!ft_div_bigint(val, exp))
			return (0);
	}
	return (1);
}

int				ft_get_string(t_pf_arg *instr, long double num)
{
	long int			exp;
	long long unsigned	mnt;
	t_bigint			*val;

	val = (t_bigint *)malloc(sizeof(t_bigint));
	if (!val)
		return (0);
	if (!ft_frexp(num, &exp, val, &mnt))
		return (0);
	exp -= 63;
	if (mnt == 0)
		return (ft_zero_string(instr, val));
	if (ft_isnan(num) || ft_isinf(num))
		return (ft_string_exceptions(num, instr, val));
	ft_create_bigint(mnt, exp, val);
	if (!ft_scale_by_exp(exp, val))
		return (0);
	return (ft_make_output(instr, val, exp));
}

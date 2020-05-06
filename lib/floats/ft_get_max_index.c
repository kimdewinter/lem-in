/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_max_index.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 14:01:46 by lravier        #+#    #+#                */
/*   Updated: 2019/10/30 14:04:12 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"
#include "../libft/libft.h"

int		get_maxind(t_bigint *val, t_pf_arg *instr, int mult)
{
	int res;
	int add;

	add = val->startind;
	if (val->startind == -1)
		add++;
	res = 0;
	while (mult)
	{
		res++;
		mult /= 10;
	}
	res += ((ARR - 1) - add) * 6;
	if (res < instr->precision)
		return (res);
	else
		return (instr->precision);
}

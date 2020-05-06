/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_create_output.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 16:00:33 by lravier        #+#    #+#                */
/*   Updated: 2019/11/09 16:47:53 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"
#include "../libft/libft.h"

static int		ft_e_to_str(t_pf_arg *instr, t_bigint *val, long int exp)
{
	int fact;
	int mult;

	fact = 0;
	mult = ft_scale_bigint(val, instr, &fact, exp);
	if (!ft_create_string_e(instr, val, mult, fact))
		return (0);
	return (1);
}

static int		ft_f_to_str(t_pf_arg *instr, t_bigint *val)
{
	ft_round_bigint(val, instr->precision, instr);
	if (!ft_create_string(instr, val))
		return (0);
	return (1);
}

int				ft_make_output(t_pf_arg *instr, t_bigint *val, long int exp)
{
	if (instr->conversion == 'E' || instr->conversion == 'e')
		return (ft_e_to_str(instr, val, exp));
	if (instr->conversion == 'F' || instr->conversion == 'f')
		return (ft_f_to_str(instr, val));
	if (instr->conversion == 'G' || instr->conversion == 'g')
		return (ft_conv_g(instr, val, exp));
	return (0);
}

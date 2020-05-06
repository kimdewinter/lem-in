/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_adj_flags_precision.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/06 15:21:23 by lravier        #+#    #+#                */
/*   Updated: 2019/11/08 10:20:51 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static int		adjust_fw(t_pf_arg *instr)
{
	if (instr->field_width == INT_MIN)
		return (0);
	if (instr->field_width < 0)
	{
		instr->flags[2] = 1;
		instr->field_width *= -1;
	}
	return (1);
}

static void		adjust_hash(t_pf_arg *instr)
{
	if (!has_alt_form(instr->conversion))
		instr->flags[0] = 0;
	if (instr->conversion == 'p')
		instr->flags[0] = 1;
}

static void		adjust_zero(t_pf_arg *instr)
{
	if (!(is_numeric_conversion(instr->conversion)))
		instr->flags[1] = 0;
	if (instr->flags[2] == 1)
		instr->flags[1] = 0;
	if (instr->precision >= 0 && is_dioux(instr->conversion))
		instr->flags[1] = 0;
}

static void		adjust_plus(t_pf_arg *instr)
{
	if (!is_signed_conversion(instr->conversion) || instr->conversion == 's')
		instr->flags[4] = 0;
	if (instr->flags[4] == 1)
		instr->flags[3] = 0;
}

int				adjust_flags_precision(t_pf_arg **instructions)
{
	t_pf_arg *instr;

	instr = *instructions;
	while (instr)
	{
		if (!adjust_fw(instr))
			return (0);
		adjust_hash(instr);
		adjust_zero(instr);
		adjust_plus(instr);
		adjust_lm(instr);
		if (instr->precision < 0)
			set_default_prec(instr);
		if (instr->precision == 0 &&
		(instr->conversion == 'g' || instr->conversion == 'G'))
			instr->precision = 1;
		if (!is_signed_conversion(instr->conversion))
			instr->flags[3] = 0;
		instr = instr->next;
	}
	return (1);
}

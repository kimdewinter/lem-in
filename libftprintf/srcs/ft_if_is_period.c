/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_if_is_period.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 13:24:14 by lravier        #+#    #+#                */
/*   Updated: 2019/11/11 12:01:42 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static void		next_is_dollar(const char *format, int *i, int *curr,
t_pf_arg *instr)
{
	(*i)++;
	instr->prec_no = ft_atoi(&format[*i]);
	*curr = instr->prec_no;
	skip_digits(format, i);
	(*i)++;
}

static void		next_is_ast(const char *format, int *i, int *curr,
t_pf_arg *instr)
{
	int j;

	(*i)++;
	if (is_number(format[(*i) + 1]))
	{
		j = *i;
		j++;
		skip_digits(format, &j);
		if (format[j] == '$')
			next_is_dollar(format, i, curr, instr);
		else
		{
			(*i)++;
			(*curr)++;
			instr->prec_no = *curr;
		}
	}
	else
	{
		(*i)++;
		(*curr)++;
		instr->prec_no = *curr;
	}
}

void			if_is_period(const char *format, int *i, int *curr,
t_pf_arg *instr)
{
	if (is_number(format[(*i) + 1]))
	{
		(*i)++;
		instr->precision = ft_atoi(&format[*i]);
		skip_digits(format, i);
	}
	else if (format[*i + 1] == '*')
		next_is_ast(format, i, curr, instr);
	else
	{
		(*i)++;
		instr->precision = 0;
	}
}

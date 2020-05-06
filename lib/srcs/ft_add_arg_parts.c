/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_add_arg_parts.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/06 14:48:43 by lravier        #+#    #+#                */
/*   Updated: 2019/11/11 12:01:42 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

void			add_flag(char c, int *i, t_pf_arg *instr)
{
	if (c == '#')
		instr->flags[0] = 1;
	if (c == '0')
		instr->flags[1] = 1;
	if (c == '-')
		instr->flags[2] = 1;
	if (c == ' ')
		instr->flags[3] = 1;
	if (c == '+')
		instr->flags[4] = 1;
	(*i)++;
}

void			if_is_number(const char *format, int *i,
int *curr, t_pf_arg *instr)
{
	int j;
	int k;

	j = *i;
	k = j - 1;
	skip_digits(format, &j);
	while (is_flag(format[k]))
		k--;
	if (format[j] == '$' && format[k] == '%')
	{
		instr->conv_no = ft_atoi(&format[*i]);
		*curr = instr->conv_no;
		skip_digits(format, i);
		(*i)++;
	}
	else
	{
		instr->field_width = ft_atoi(&format[*i]);
		skip_digits(format, i);
	}
}

static void		set_fw(int *curr, t_pf_arg *instr, int *i)
{
	(*curr)++;
	instr->fw_no = *curr;
	(*i)++;
}

void			if_is_asterisk(const char *format, int *i,
int *curr, t_pf_arg *instr)
{
	int j;

	if (is_number(format[*i + 1]))
	{
		(*i)++;
		j = *i;
		skip_digits(format, &j);
		if (format[j] == '$')
		{
			instr->fw_no = ft_atoi(&format[*i]);
			*curr = instr->fw_no;
			(j)++;
		}
		else
		{
			(*curr)++;
			instr->field_width = ft_atoi(&format[*i]);
		}
		*i = j;
	}
	else
		set_fw(curr, instr, i);
}

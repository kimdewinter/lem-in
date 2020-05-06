/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parse_format.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 13:28:54 by lravier        #+#    #+#                */
/*   Updated: 2019/11/11 13:07:13 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

void				if_is_conversion(const char *format, int *i,
int *curr, t_pf_arg *instr)
{
	instr->conversion = format[*i];
	if (instr->conv_no == 0 || format[*i - 1] == '*')
	{
		(*curr)++;
		instr->conv_no = *curr;
	}
	instr->end_ind = *i;
	(*i)++;
}

static void			set_conv_def(const char *format, int *i,
int *curr, t_pf_arg *instr)
{
	if (is_conversion(format[*i]))
		if_is_conversion(format, i, curr, instr);
	else
		instr->end_ind = *i;
	set_datatype(instr);
	instr->datasize = get_size_of_datatype(instr->datatype);
}

static void			get_instruction(const char *format,
int *i, int *curr, t_pf_arg *instr)
{
	instr->s_ind = *i;
	(*i)++;
	while (is_valid(format[*i]))
	{
		if (is_number(format[*i]))
			if_is_number(format, i, curr, instr);
		if (format[*i] == '.')
			if_is_period(format, i, curr, instr);
		if (format[*i] == '*')
			if_is_asterisk(format, i, curr, instr);
		if (is_flag(format[*i]))
			add_flag(format[*i], i, instr);
		if (is_lm(format[*i]))
			add_lm(format, i, instr);
	}
	set_conv_def(format, i, curr, instr);
}

int					ft_parse_format(const char *format,
t_pf_arg **instructions)
{
	int			i;
	int			curr_arg;
	t_pf_arg	*instr;

	i = 0;
	curr_arg = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '%')
		{
			instr = initialize_arg();
			if (instr == NULL)
				return (0);
			get_instruction(format, &i, &curr_arg, instr);
			ft_pflstaddend(instr, instructions);
		}
		else if (format[i + 1] == '%' && format[i] == '%')
			i += 2;
		else
			i++;
	}
	return (1);
}

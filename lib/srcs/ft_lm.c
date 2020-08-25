/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lm.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/06 15:00:30 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/25 17:11:20 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static void	add_lm_l(int *i, const char *format, t_pf_arg *instr)
{
	int	j;

	j = 0;
	while (format[*i] == 'l' && j < 2)
	{
		(*i)++;
		j++;
	}
	if (j == 2)
		instr->length_mods = 4;
	else
		instr->length_mods = 3;
}

static void	add_lm_h(int *i, const char *format, t_pf_arg *instr)
{
	int	j;

	j = 0;
	while (format[*i] == 'h' && j < 2)
	{
		(*i)++;
		j++;
	}
	if (j == 2)
		instr->length_mods = 1;
	else
		instr->length_mods = 2;
}

void		add_lm(const char *format, int *i, t_pf_arg *instr)
{
	if (format[*i] == 'l')
		add_lm_l(i, format, instr);
	else if (format[*i] == 'h')
		add_lm_h(i, format, instr);
	else
	{
		instr->length_mods = 5;
		(*i)++;
	}
}

void		adjust_lm(t_pf_arg *instr)
{
	if (instr->length_mods == 5)
	{
		if (!(instr->conversion == 'e' || instr->conversion == 'E' ||
		instr->conversion == 'f' || instr->conversion == 'F' ||
		instr->conversion == 'g' || instr->conversion == 'G'))
			instr->length_mods = 0;
	}
}

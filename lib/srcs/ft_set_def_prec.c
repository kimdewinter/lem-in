/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_set_def_prec.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 13:58:12 by lravier        #+#    #+#                */
/*   Updated: 2019/10/08 13:59:08 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

void	skip_digits(const char *str, int *i)
{
	while (ft_isdigit(str[*i]))
		(*i)++;
}

void	set_default_prec(t_pf_arg *instr)
{
	if (instr->conversion == 'd' || instr->conversion == 'i' ||
	instr->conversion == 'o' || instr->conversion == 'u' ||
	instr->conversion == 'x' || instr->conversion == 'X' ||
	instr->conversion == 'p')
		instr->precision = 1;
	if (instr->conversion == 'e' || instr->conversion == 'E' ||
	instr->conversion == 'f' || instr->conversion == 'F' ||
	instr->conversion == 'g' || instr->conversion == 'G')
		instr->precision = 6;
}

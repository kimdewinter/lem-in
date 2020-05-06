/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calculate_length_u.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/06 15:26:14 by lravier        #+#    #+#                */
/*   Updated: 2019/11/07 15:29:16 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static void		check_flags_len(int *len, t_pf_arg *instr, uintmax_t num,
int calc_len)
{
	if (instr->flags[0] == 1)
	{
		if ((num == 0 && instr->precision == 0) && !(instr->conversion == 'o'))
			return ;
		if (instr->conversion == 'o' && !(calc_len < *len))
			(*len)++;
		if ((instr->conversion == 'X' || instr->conversion == 'x' ||
		instr->conversion == 'p') && num != 0)
			*len += 2;
	}
}

static void		check_prec_len(int *len, t_pf_arg *instr)
{
	if (instr->precision > *len)
	{
		*len = instr->precision;
		if (instr->flags[3] == 1 || instr->flags[4] == 1)
			(*len)++;
	}
}

int				get_int_len_u(uintmax_t num, t_pf_arg *instr, int base)
{
	int			len;
	uintmax_t	tmp;
	int			calc_len;

	len = 0;
	calc_len = 0;
	tmp = num;
	if (num == 0 && instr->precision != 0)
		len++;
	else
	{
		while (tmp > 0)
		{
			tmp /= base;
			len++;
		}
		calc_len = len;
		if (len < instr->precision)
			len = instr->precision;
	}
	check_flags_len(&len, instr, num, calc_len);
	check_prec_len(&len, instr);
	return (len);
}

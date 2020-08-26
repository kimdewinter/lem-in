/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calculate_length.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/06 15:27:39 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/26 10:43:45 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static void	check_flags_prec_len(int *len, t_pf_arg *instr, intmax_t num)
{
	if (instr->precision > *len)
		*len = instr->precision;
	if (num < 0 || instr->flags[3] == 1 || instr->flags[4] == 1)
		(*len)++;
}

static int	handle_zero(intmax_t num, t_pf_arg *instr)
{
	int len;

	len = 0;
	if (instr->precision != 0)
		len++;
	check_flags_prec_len(&len, instr, num);
	return (len);
}

int			get_int_len(intmax_t num, t_pf_arg *instr, int base)
{
	int			len;
	intmax_t	tmp;

	len = 0;
	tmp = num;
	if (num == (-9223372036854775807LL - 1))
		return (20);
	if (num == 0)
		return (handle_zero(num, instr));
	else if (num < 0)
		tmp *= -1;
	while (tmp > 0)
	{
		tmp /= base;
		len++;
	}
	check_flags_prec_len(&len, instr, num);
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_di.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 13:05:57 by lravier        #+#    #+#                */
/*   Updated: 2019/10/13 20:40:43 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

int		ft_handle_di(t_pf_arg *instr)
{
	intmax_t num;

	num = get_number(instr);
	instr->len = get_int_len(num, instr, 10);
	instr->tmp = ft_strnew(sizeof(char) * instr->len);
	if (!instr->tmp)
		return (0);
	if (instr->len != 0)
	{
		if (num == INT_MAX_MIN)
			ft_strcpy(instr->tmp, "-9223372036854775808");
		else
		{
			ft_memset(instr->tmp, '0', instr->len);
			put_nbr(num, instr, instr->len, 10);
		}
	}
	return (1);
}

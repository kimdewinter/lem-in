/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_b.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 13:04:51 by lravier        #+#    #+#                */
/*   Updated: 2019/10/08 13:05:17 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

int		ft_handle_b(t_pf_arg *instr)
{
	uintmax_t num;

	num = get_unsigned_number(instr);
	instr->len = get_int_len_u(num, instr, 2);
	instr->tmp = ft_strnew(sizeof(char) * instr->len);
	if (!instr->tmp)
		return (0);
	ft_memset(instr->tmp, '0', instr->len);
	if (instr->len != 0)
		put_nbr_u(num, instr, instr->len, 2);
	return (1);
}

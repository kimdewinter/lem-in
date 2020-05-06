/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_o.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 13:10:01 by lravier        #+#    #+#                */
/*   Updated: 2019/11/06 15:39:48 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

int		ft_handle_o(t_pf_arg *instr)
{
	uintmax_t num;

	num = get_unsigned_number(instr);
	instr->len = get_int_len_u(num, instr, 8);
	instr->tmp = ft_strnew(sizeof(char) * instr->len);
	if (!instr->tmp)
		return (0);
	ft_memset(instr->tmp, '0', instr->len);
	if (instr->len != 0)
		put_nbr_u(num, instr, instr->len, 8);
	return (1);
}

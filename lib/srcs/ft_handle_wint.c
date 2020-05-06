/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_wint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 13:14:20 by lravier        #+#    #+#                */
/*   Updated: 2019/10/30 14:49:23 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static int			get_len_wchar(wint_t num)
{
	if (num <= 0x7F)
		return (1);
	else if (num <= 0x7FF)
		return (2);
	else if (num <= 0xFFFF)
		return (3);
	else if (num <= 0x10FFFF)
		return (4);
	else
		return (0);
}

static void			put_wint_char2(t_pf_arg *instr, wint_t num, int ind)
{
	instr->tmp[ind] = (num >> 6) + 192;
	instr->tmp[ind + 1] = ((num & 63) + 128);
}

static void			put_wint_char3(t_pf_arg *instr, wint_t num, int ind)
{
	instr->tmp[ind] = (num >> 12) + 224;
	instr->tmp[ind + 1] = ((num >> 6) & 63) + 128;
	instr->tmp[ind + 2] = ((num & 63) + 128);
}

static void			put_wint_char4(t_pf_arg *instr, wint_t num, int ind)
{
	instr->tmp[ind] = (num >> 18) + 240;
	instr->tmp[ind + 1] = ((num >> 12) & 63) + 128;
	instr->tmp[ind + 2] = ((num >> 6) & 63) + 128;
	instr->tmp[ind + 3] = ((num & 63) + 128);
}

int					ft_handle_wint(t_pf_arg *instr)
{
	wint_t num;

	num = *(wint_t *)(instr->data);
	instr->len = get_len_wchar(num);
	instr->tmp = ft_strnew(instr->len);
	if (!instr->tmp)
		return (0);
	if (instr->len == 1)
		instr->tmp[0] = num;
	if (instr->len == 2)
		put_wint_char2(instr, num, 0);
	if (instr->len == 3)
		put_wint_char3(instr, num, 0);
	if (instr->len == 4)
		put_wint_char4(instr, num, 0);
	return (1);
}

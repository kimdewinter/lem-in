/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_s.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 13:12:07 by lravier        #+#    #+#                */
/*   Updated: 2019/11/08 10:19:18 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

int			ft_handle_s(t_pf_arg *instr)
{
	int len;

	len = 0;
	if (instr->data == NULL)
	{
		if (!ft_strnull(instr))
			return (0);
	}
	else
	{
		instr->len = ft_strlen((char *)instr->data);
		len = instr->len;
		if (instr->flags[3] == 1 && len == 0)
			instr->len++;
		if (instr->precision >= 0 && instr->precision < instr->len)
			instr->len = instr->precision;
		instr->tmp = ft_strnew(instr->len);
		if (!instr->tmp)
			return (0);
		if (instr->flags[3] == 1 && len == 0)
			instr->tmp[0] = ' ';
		else
			ft_strncpy(instr->tmp, (char*)instr->data, instr->len);
	}
	return (1);
}

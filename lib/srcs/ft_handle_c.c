/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_c.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/06 15:49:41 by lravier        #+#    #+#                */
/*   Updated: 2019/11/11 11:51:11 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static int	handle_nc(t_pf_arg *instr)
{
	unsigned char c;

	c = *((unsigned char *)instr->data);
	instr->len = 1;
	instr->tmp = ft_strnew(1);
	if (!instr->tmp)
		return (0);
	instr->tmp[0] = c;
	return (1);
}

int			ft_handle_c(t_pf_arg *instr)
{
	if (ft_strcmp(instr->datatype, U_CHAR) == 0)
		return (handle_nc(instr));
	return (ft_handle_wint(instr));
}

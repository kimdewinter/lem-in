/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_result.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/06 14:32:34 by lravier        #+#    #+#                */
/*   Updated: 2019/11/11 12:01:42 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static int	get_result_other(t_pf_arg *instr)
{
	if (instr->conversion == 'e' || instr->conversion == 'E')
		return (ft_handle_e(instr));
	if (instr->conversion == 'f' || instr->conversion == 'F')
		return (ft_handle_f(instr));
	if (instr->conversion == 'g' || instr->conversion == 'G')
		return (ft_handle_g(instr));
	return (0);
}

int			get_result(t_pf_arg *instr, const char *format)
{
	if (instr->conversion == '0')
		return (ft_handle_empty(instr, format));
	if (instr->conversion == 'i' || instr->conversion == 'd')
		return (ft_handle_di(instr));
	if (instr->conversion == 'o')
		return (ft_handle_o(instr));
	if (instr->conversion == 'u')
		return (ft_handle_u(instr));
	if (instr->conversion == 'x' || instr->conversion == 'X')
		return (ft_handle_x(instr));
	if (instr->conversion == 'b')
		return (ft_handle_b(instr));
	if (instr->conversion == 'p')
		return (ft_handle_p(instr));
	if (instr->conversion == 'c')
		return (ft_handle_c(instr));
	if (instr->conversion == 's')
		return (ft_handle_s(instr));
	else
		return (get_result_other(instr));
}

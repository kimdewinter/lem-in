/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_write_output.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 14:07:21 by lravier        #+#    #+#                */
/*   Updated: 2019/10/30 14:50:14 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static int	ft_write_padding(int padding, char c, t_writer *wrt, char first)
{
	char	*padd;
	int		res;

	if (padding <= 0)
		return (1);
	padd = ft_strnew(padding);
	if (!padd)
		return (0);
	ft_memset(padd, c, padding);
	if (first == 'x' || first == 'X')
		padd[1] = first;
	else
		padd[0] = first;
	res = wrt->ft_write(padd, padding, wrt);
	free(padd);
	return (res);
}

static int	ft_wrt_left_adj(t_writer *wrt, t_pf_arg *instr, int padding)
{
	if (!wrt->ft_write(instr->tmp, instr->len, wrt))
		return (0);
	return (ft_write_padding(padding, ' ', wrt, ' '));
}

static int	ft_wrt_zero_padded(t_writer *wrt, t_pf_arg *instr, int padding)
{
	if (is_signed_conversion(instr->conversion) &&
	(instr->flags[3] == 1 || instr->flags[4] == 1 ||
	instr->tmp[0] == '-') && padding >= 1)
	{
		padding++;
		if (!ft_write_padding(padding, '0', wrt, instr->tmp[0]))
			return (0);
		return (wrt->ft_write(&instr->tmp[1],
		instr->len - 1, wrt));
	}
	else if ((instr->conversion == 'p' || instr->conversion == 'x' ||
	instr->conversion == 'X') && instr->flags[0] == 1 && padding >= 1)
	{
		padding += 2;
		if (!ft_write_padding(padding, '0', wrt, instr->tmp[1]))
			return (0);
		return (wrt->ft_write(&instr->tmp[2], instr->len - 2, wrt));
	}
	else
	{
		if (!ft_write_padding(padding, '0', wrt, '0'))
			return (0);
		return (wrt->ft_write(instr->tmp, instr->len, wrt));
	}
}

int			ft_write_output(t_pf_arg *instr, t_writer *wrt)
{
	int padding;

	padding = instr->field_width - instr->len;
	if (instr->flags[2])
		return (ft_wrt_left_adj(wrt, instr, padding));
	else
	{
		if (instr->flags[1] == 1)
			return (ft_wrt_zero_padded(wrt, instr, padding));
		if (!ft_write_padding(padding, ' ', wrt, ' '))
			return (0);
		return (wrt->ft_write(instr->tmp, instr->len, wrt));
	}
}

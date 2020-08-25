/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_e.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 13:06:46 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/25 17:11:20 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../floats/includes/floats.h"

int		ft_handle_e(t_pf_arg *instr)
{
	long double num;

	num = get_double(instr);
	if (!ft_get_string(instr, num))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_di.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 12:59:29 by lravier        #+#    #+#                */
/*   Updated: 2019/10/08 13:00:23 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static int		set_prefix(intmax_t *num, t_pf_arg *instr)
{
	int i;

	i = 0;
	if ((*num) < 0)
	{
		instr->tmp[i] = '-';
		(*num) *= -1;
		i++;
	}
	else
	{
		if (instr->flags[3] == 1)
		{
			instr->tmp[i] = ' ';
			i++;
		}
		if (instr->flags[4] == 1)
		{
			instr->tmp[i] = '+';
			i++;
		}
	}
	return (i);
}

static void		num_to_str_base(intmax_t num, t_pf_arg *instr, int i, int base)
{
	while (num > 0)
	{
		instr->tmp[i] = (num % base) + '0';
		i--;
		num /= base;
	}
}

void			put_nbr(intmax_t num, t_pf_arg *instr, int len, int base)
{
	int i;
	int j;

	j = len - 1;
	i = set_prefix(&num, instr);
	if (i != len)
		num_to_str_base(num, instr, j, base);
}

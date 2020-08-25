/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_fill_string_e.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 16:08:22 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/25 17:11:20 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"
#include "../libft/libft.h"

int				ft_add_len_fact(int fact)
{
	int len;
	int mult;

	mult = 100;
	len = 2;
	fact = ft_abs(fact);
	while (fact / mult >= 1)
	{
		len++;
		mult *= 10;
	}
	return (len);
}

static void		ft_add_exp_prefix(t_pf_arg *instr, int *i, int fact)
{
	if (instr->conversion == 'E')
		instr->tmp[*i] = 'E';
	else
		instr->tmp[*i] = 'e';
	(*i)++;
	if (fact < 0)
		instr->tmp[*i] = '-';
	else
		instr->tmp[*i] = '+';
	(*i)++;
}

void			ft_add_exp(t_pf_arg *instr, int fact, int i)
{
	int len;
	int mlt;
	int tmp;

	mlt = 1;
	ft_add_exp_prefix(instr, &i, fact);
	fact = (int)ft_abs(fact);
	len = ft_add_len_fact(fact);
	while (len > 1)
	{
		mlt *= 10;
		len--;
	}
	while (mlt)
	{
		tmp = fact / mlt;
		instr->tmp[i] = tmp + '0';
		fact -= mlt * tmp;
		mlt /= 10;
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_fill_str.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 16:01:43 by lravier        #+#    #+#                */
/*   Updated: 2019/10/13 17:37:08 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"
#include "../libft/libft.h"

void			ft_first_place(t_pf_arg *instr, t_bigint val, int *j)
{
	if (val.sign == 1)
	{
		instr->tmp[*j] = '-';
		(*j)++;
	}
	else
	{
		if (instr->flags[3] == 1)
		{
			instr->tmp[*j] = ' ';
			(*j)++;
		}
		if (instr->flags[4] == 1)
		{
			instr->tmp[*j] = '+';
			(*j)++;
		}
	}
}

void			ft_start_fact(uint32_t *fract, uint32_t *factor, t_bigint val)
{
	int i;

	i = val.startind;
	*factor = BASE;
	*fract = val.big[i] / *factor;
	while (!*fract && *factor)
	{
		*fract = val.big[i] / *factor;
		*factor /= 10;
	}
	if (*factor == 0)
		*factor = 1;
	else
		*factor *= 10;
}

static void		ft_set_zero(t_pf_arg *instr, int *j)
{
	instr->tmp[*j] = '0';
	(*j)++;
}

void			ft_fill_dec(t_pf_arg *instr, t_bigint val, int *j)
{
	int			i;
	int			k;
	uint32_t	factor;
	uint32_t	fract;

	i = val.startind;
	k = *j;
	if (val.startind == -1 && val.biggest_exp == -1)
		(*j)++;
	ft_start_fact(&fract, &factor, val);
	while (i < val.biggest_exp)
	{
		while (factor)
		{
			fract = val.big[i] / factor;
			instr->tmp[*j] = fract + '0';
			val.big[i] -= fract * factor;
			factor /= 10;
			(*j)++;
		}
		factor = BASE / 10;
		i++;
	}
	if (*j == k)
		ft_set_zero(instr, j);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_create_string.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 15:19:04 by lravier        #+#    #+#                */
/*   Updated: 2019/11/09 16:48:28 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"
#include "../libft/libft.h"

static void		ft_nfract_nstate(int *state, uint32_t *factor,
uint32_t *fract, uint32_t big)
{
	if (*fract)
		*state = 1;
	if (!*fract && *state == 0)
	{
		(*state) = 1;
		(*factor) /= 10;
		(*fract) = big / (*factor);
	}
}

static int		ft_setup(uint32_t *factor, int *state, t_bigint val, int *i)
{
	(*state) = 0;
	(*factor) = BASE;
	(*i) = val.biggest_exp;
	if (*i == -1)
	{
		*i = 0;
		return (val.zeros * DECPLB);
	}
	return (0);
}

static void		ft_fill_fract(t_pf_arg *instr, t_bigint val, int *j)
{
	int			i;
	uint32_t	factor;
	uint32_t	fract;
	int			state;

	*j += ft_setup(&factor, &state, val, &i);
	while (*j < instr->len && i < ARR)
	{
		while (factor && *j < instr->len && i < ARR)
		{
			fract = val.big[i] / factor;
			ft_nfract_nstate(&state, &factor, &fract, val.big[i]);
			if (state)
			{
				instr->tmp[*j] = fract + '0';
				val.big[i] -= fract * factor;
				(*j)++;
			}
			factor /= 10;
		}
		factor = BASE / 10;
		i++;
	}
}

static void		ft_fill_string(t_pf_arg *instr, t_bigint val)
{
	int j;

	j = 0;
	ft_first_place(instr, val, &j);
	ft_fill_dec(instr, val, &j);
	if (j < instr->len)
	{
		instr->tmp[j] = '.';
		j++;
	}
	ft_fill_fract(instr, val, &j);
}

int				ft_create_string(t_pf_arg *instr, t_bigint *val)
{
	ft_get_len_f(instr, val);
	instr->tmp = ft_strnew(instr->len);
	if (!instr->tmp)
		return (0);
	ft_memset(instr->tmp, '0', instr->len);
	ft_fill_string(instr, *val);
	free(val);
	return (1);
}

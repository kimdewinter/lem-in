/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_oucxX.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 13:26:54 by lravier        #+#    #+#                */
/*   Updated: 2019/10/08 13:27:53 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static void		set_x(char *res, t_pf_arg *instr, int *i, uintmax_t num)
{
	if ((instr->conversion == 'x' || instr->conversion == 'X' ||
	instr->conversion == 'p') && num != 0)
	{
		(*i)++;
		if (instr->conversion == 'p')
			res[*i] = 'x';
		else
			res[*i] = instr->conversion;
		(*i)++;
	}
	else
		instr->flags[0] = 0;
}

static int		set_prefix_u(uintmax_t *num, char *res, t_pf_arg *instr)
{
	int i;

	i = 0;
	if (instr->flags[0] == 1 && !(*num == 0 && instr->precision == 0))
		set_x(res, instr, &i, *num);
	return (i);
}

static void		num_to_str_base_u(uintmax_t num, t_pf_arg *instr, int i,
int base)
{
	char		c;
	char		*res;
	intmax_t	tmp;

	res = instr->tmp;
	while (num > 0)
	{
		tmp = num % base;
		if (tmp >= 10)
		{
			if (instr->conversion == 'X')
				c = 'A' + (tmp - 10);
			else
				c = 'a' + (tmp - 10);
		}
		else
			c = tmp + '0';
		res[i] = c;
		i--;
		num /= base;
	}
}

void			put_nbr_u(uintmax_t num, t_pf_arg *instr, int len, int base)
{
	int i;
	int j;

	j = len - 1;
	i = set_prefix_u(&num, instr->tmp, instr);
	if (i != len)
		num_to_str_base_u(num, instr, j, base);
}

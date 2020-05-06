/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_create_bigint.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 15:16:12 by lravier        #+#    #+#                */
/*   Updated: 2019/11/09 14:20:37 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"
#include "../libft/libft.h"

static void	set_zero(t_bigint *val)
{
	int i;

	i = 0;
	while (i < ARR)
	{
		val->big[i] = 0;
		i++;
	}
}

void		ft_create_bigint(unsigned long long n, long int exp, t_bigint *val)
{
	unsigned long long	tmp;
	int					i;
	int					offset;

	set_zero(val);
	tmp = n;
	i = 0;
	while (tmp)
	{
		tmp /= BASE;
		i++;
	}
	val->zeros = 0;
	val->biggest_exp = i;
	i--;
	offset = 0;
	if (exp > 0)
		offset = 127 - i;
	val->startind = offset;
	while (i >= 0)
	{
		val->big[i + offset] = n % BASE;
		n /= BASE;
		i--;
	}
}

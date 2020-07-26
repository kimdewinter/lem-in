/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prime.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 12:01:12 by lravier       #+#    #+#                 */
/*   Updated: 2020/04/29 18:08:25 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hashing.h"

static int	is_prime(int n)
{
	int i;

	if (n < 2)
		return (-1);
	if (n < 4)
		return (1);
	if (n % 2 == 0)
		return (0);
	i = 3;
	while (ft_pow(i, 2) <= n)
	{
		if (n % i == 0)
			return (0);
		i += 2;
	}
	return (1);
}

int		next_prime(int n)
{
	while (!is_prime(n))
		n++;
	return (n);
}

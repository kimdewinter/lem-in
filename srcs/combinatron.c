/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   combinatron.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/22 16:03:32 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/22 16:12:56 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static size_t		ft_factorial(size_t	n)
{
	if (n == 0)
		return (1);
	return (n * ft_factorial(n - 1));
}

ssize_t		combinatron(const size_t n)
{
	// (n!) / (r!(n-r)!);
	size_t	result;
	size_t	i;

	result = n;
	i = 1;
	while (i < n)
	{
		result += ft_factorial(n - i) /
		(ft_factorial(i) * ft_factorial(n - i));
		i++;
	}
	return (result);
}

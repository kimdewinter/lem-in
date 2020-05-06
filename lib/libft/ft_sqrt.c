/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sqrt.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 12:02:53 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/28 12:21:13 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sqrt(int n)
{
	int i;
	int check;

	i = 0;
	check = 0;
	if (n < 0)
		return (-1);
	if (n == 0 || n == 1)
		return (n);
	if (n % 2 == 0)
		i = 2;
	else
		i = 3;
	check = i * i;
	while (check < n)
	{
		i += 2;
		check = i * i;
	}
	if (check == n)
		return (i);
	return (-1);
}

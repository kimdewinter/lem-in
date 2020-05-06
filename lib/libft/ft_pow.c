/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pow.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 17:36:12 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/28 17:46:37 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_pow(int base, int pow)
{
	if (pow == 0)
		return (1);
	else
	{
		return (base * ft_pow(base, pow - 1));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pow_ll.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 18:08:38 by lravier       #+#    #+#                 */
/*   Updated: 2020/04/29 18:12:51 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hashing.h"

long long unsigned	ft_pow_ll(int base, int pow)
{
	if (pow == 0)
		return (1);
	return (base * ft_pow_ll(base, pow - 1));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/21 19:18:59 by lravier        #+#    #+#                */
/*   Updated: 2019/09/06 15:15:54 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnew(size_t size)
{
	char *res;

	res = (char *)malloc((sizeof(char) * size) + 1);
	if (res)
	{
		ft_bzero(res, size + 1);
		return (res);
	}
	else
		return (NULL);
}

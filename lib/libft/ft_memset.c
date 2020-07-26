/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/20 10:29:14 by lravier        #+#    #+#                */
/*   Updated: 2019/06/26 18:57:46 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *arr, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char*)arr;
	i = 0;
	while (i < n)
	{
		*ptr = c;
		ptr++;
		i++;
	}
	return (arr);
}

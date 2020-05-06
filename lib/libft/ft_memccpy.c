/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/22 16:05:34 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/28 10:28:02 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memccpy(void *dst, const void *src, int c,
size_t n)
{
	void *start;

	start = ft_memchr(src, c, n);
	if (start)
		return (ft_mempcpy(dst, src, start - src + 1));
	ft_memcpy(dst, src, n);
	return (NULL);
}

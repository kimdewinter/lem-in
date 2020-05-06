/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/24 09:28:12 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/24 12:05:25 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *d;
	unsigned char *s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d < s)
		dst = ft_memcpy(dst, src, len);
	else
	{
		d += len - 1;
		s += len - 1;
		while (len > 0)
		{
			*d = *s;
			len--;
			d--;
			s--;
		}
	}
	return (dst);
}

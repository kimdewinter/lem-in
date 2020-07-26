/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/24 12:06:28 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/24 13:25:36 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char t;
	unsigned char *src;

	t = (unsigned char)c;
	src = (unsigned char *)s;
	while (n > 0)
	{
		if (*src == t)
			return (src);
		n--;
		src++;
	}
	return (NULL);
}

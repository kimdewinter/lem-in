/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/24 13:26:19 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/24 14:06:21 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *s;
	unsigned char *d;

	s = (unsigned char *)s1;
	d = (unsigned char *)s2;
	while (n > 0)
	{
		if (*s != *d)
			return (*s - *d);
		s++;
		d++;
		n--;
	}
	return (0);
}

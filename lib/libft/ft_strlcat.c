/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/22 11:29:46 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/26 15:56:49 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t dstlen;
	size_t srclen;
	size_t i;
	size_t j;

	j = 0;
	i = 0;
	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (size < dstlen)
		i = size;
	else
		i = dstlen;
	while (src[j] != '\0' && (j + i + 1) < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (size > i)
		dst[i + j] = '\0';
	return (i + srclen);
}

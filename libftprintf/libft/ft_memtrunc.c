/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memtrunc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/09 09:16:04 by lravier       #+#    #+#                 */
/*   Updated: 2019/04/16 16:17:11 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memtrunc(void **orig, size_t start, size_t len)
{
	unsigned char	*res;
	unsigned char	*src;
	size_t			j;

	j = 0;
	src = (unsigned char *)*orig;
	res = (unsigned char *)ft_memalloc(len - start);
	if (!res)
		return (0);
	while (start < len)
	{
		res[j] = src[start];
		start++;
		j++;
	}
	if (*orig)
		ft_memdel(orig);
	*orig = (void *)res;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/31 10:24:11 by lravier       #+#    #+#                 */
/*   Updated: 2019/04/16 18:41:14 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memrealloc(void **ptr, size_t prev_size, size_t size)
{
	unsigned char	*buff;
	size_t			mlen;

	buff = NULL;
	mlen = size;
	if (size <= prev_size)
		mlen = prev_size;
	buff = ft_memalloc(mlen);
	if (!buff)
		return (0);
	if (mlen > 0)
		ft_memcpy(buff, *ptr, prev_size);
	if (*ptr)
		free(*ptr);
	*ptr = (void *)buff;
	return (1);
}

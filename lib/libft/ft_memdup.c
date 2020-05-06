/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/04 13:05:48 by lravier       #+#    #+#                 */
/*   Updated: 2019/04/12 15:40:47 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memdup(void **dst, void *src, size_t len)
{
	size_t			i;
	unsigned char	*source;
	unsigned char	*destination;

	source = (unsigned char *)src;
	i = 0;
	destination = ft_memalloc(len);
	if (!destination)
		return (0);
	while (i < len)
	{
		destination[i] = source[i];
		i++;
	}
	if (*dst)
		free(*dst);
	*dst = (void *)destination;
	return (1);
}

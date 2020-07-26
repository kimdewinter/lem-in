/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mempcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/26 11:26:40 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/26 15:35:14 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_mempcpy(void *dst, const void *src, size_t n)
{
	return ((char *)ft_memcpy(dst, src, n) + n);
}

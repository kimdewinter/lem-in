/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftd_memalloc.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/05 12:36:35 by lravier       #+#    #+#                 */
/*   Updated: 2019/04/11 12:49:10 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ftd_memalloc(void **dst, size_t size)
{
	*dst = malloc(size);
	if (*dst)
	{
		ft_bzero(*dst, size);
		return (1);
	}
	return (0);
}

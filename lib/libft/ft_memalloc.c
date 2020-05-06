/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memalloc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/20 18:57:21 by lravier        #+#    #+#                */
/*   Updated: 2019/10/13 15:55:48 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *area;

	area = malloc(size);
	if (area)
	{
		ft_bzero(area, size);
		return (area);
	}
	return (NULL);
}

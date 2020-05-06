/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnlen.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/22 14:06:13 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/22 14:07:56 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlen(const char *s, size_t max)
{
	size_t i;

	i = 0;
	while (s[i] != '\0' && i < max)
		i++;
	return (i);
}

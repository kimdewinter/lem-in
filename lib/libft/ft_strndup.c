/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/02 17:34:39 by lravier       #+#    #+#                 */
/*   Updated: 2019/04/11 12:47:37 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, size_t size)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strnew(size);
	if (!res)
		return (NULL);
	while (i < (int)size)
	{
		res[i] = s[i];
		i++;
	}
	return (res);
}

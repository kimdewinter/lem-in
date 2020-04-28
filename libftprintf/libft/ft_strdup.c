/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/22 10:50:28 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/27 15:21:24 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		len;

	len = (int)ft_strlen(s1);
	res = ft_strnew(len);
	if (!res)
		return (NULL);
	res = ft_strcpy(res, s1);
	return (res);
}

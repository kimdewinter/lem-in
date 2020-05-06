/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/21 17:29:30 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/27 15:21:50 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		len;

	str = (char *)s;
	len = (int)ft_strlen(s);
	while (len >= 0)
	{
		if (str[len] == c)
			return (&str[len]);
		len--;
	}
	return (NULL);
}

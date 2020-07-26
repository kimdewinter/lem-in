/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/24 15:30:12 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/27 18:27:11 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strnew(ft_strlen(s));
	if (!res)
		return (NULL);
	while (s[i])
	{
		res[i] = f(s[i]);
		i++;
	}
	return (res);
}

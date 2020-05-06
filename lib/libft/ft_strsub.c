/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsub.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/24 16:30:04 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/27 18:30:24 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s1, unsigned int start, size_t len)
{
	char *r;

	if (len == 0)
	{
		r = ft_strnew(0);
		if (!r)
			return (NULL);
		return (r);
	}
	r = ft_strnew(len);
	if (!r)
		return (NULL);
	ft_strncpy(r, &s1[start], len);
	return (r);
}

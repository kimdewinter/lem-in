/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrunc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/02 17:16:43 by lravier       #+#    #+#                 */
/*   Updated: 2019/04/03 14:59:32 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrunc(char *s, char *f)
{
	while (*s)
	{
		if (s == f)
			return (s);
		s++;
	}
	return (NULL);
}

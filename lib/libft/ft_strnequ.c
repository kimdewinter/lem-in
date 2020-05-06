/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnequ.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/24 16:14:46 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/28 10:23:29 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int r;

	r = ft_strncmp(s1, s2, n);
	if (r == 0)
		return (1);
	else
		return (0);
}

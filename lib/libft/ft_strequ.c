/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strequ.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/24 16:04:02 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/28 10:23:06 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	int r;

	r = ft_strcmp(s1, s2);
	if (r == 0)
		return (1);
	else
		return (0);
}

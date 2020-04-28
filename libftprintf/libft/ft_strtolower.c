/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtolower.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 17:38:20 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/29 08:51:02 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtolower(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (ft_isupper(s[i]))
			ft_tolower(s[i]);
		i++;
	}
}

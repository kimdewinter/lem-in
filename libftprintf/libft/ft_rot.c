/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrot.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 12:25:56 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/28 12:46:56 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_rot(char *str, int rot)
{
	int i;

	rot = rot % 26;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]))
		{
			if (ft_islower(str[i]))
			{
				if (str[i] - rot < 'a')
					str[i] = 'z' - (rot - (str[i] - 'a')) + 1;
				else
					str[i] -= rot;
			}
			if (ft_isupper(str[i]))
			{
				if (str[i] - rot < 'A')
					str[i] = 'Z' - (rot - (str[i] - 'A')) + 1;
				else
					str[i] -= rot;
			}
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrotr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 12:33:59 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/28 12:53:43 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_rotr(char *str, int rot)
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
				if (str[i] + rot > 'z')
					str[i] = 'a' + (rot - ('z' - str[i]));
				else
					str[i] += rot;
			}
			if (ft_isupper(str[i]))
			{
				if (str[i] + rot > 'Z')
					str[i] = 'A' + (rot - ('Z' - str[i]));
				else
					str[i] += rot;
			}
		}
		i++;
	}
}

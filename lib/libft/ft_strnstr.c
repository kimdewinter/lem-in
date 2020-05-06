/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/21 18:24:00 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/21 18:52:32 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;
	size_t check;

	i = 0;
	j = 0;
	check = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[j] != '\0' && j < len)
	{
		check = j;
		i = 0;
		while (haystack[check] == needle[i] &&
haystack[check] != '\0' && needle[i] != '\0' && check < len)
		{
			check++;
			i++;
		}
		if (needle[i] == '\0')
			return ((char *)&haystack[j]);
		j++;
	}
	return (NULL);
}

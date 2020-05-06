/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/20 18:28:37 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/21 14:01:19 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char *begin;
	char *checker;
	char *patt;

	if (needle[0] == '\0')
		return ((char *)haystack);
	begin = (char *)haystack;
	while (*begin)
	{
		checker = begin;
		patt = (char *)needle;
		while (*checker && *patt && *checker == *patt)
		{
			checker++;
			patt++;
		}
		if (!*patt)
			return (begin);
		begin++;
	}
	return (NULL);
}

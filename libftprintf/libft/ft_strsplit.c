/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/25 11:43:51 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/28 10:29:10 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_numwords(char const *s, char c)
{
	int		n;
	char	*ctr;

	n = 0;
	ctr = (char *)s;
	while (*ctr)
	{
		while (*ctr == c && *ctr)
			ctr++;
		while (*ctr != c && *ctr)
		{
			if (ctr == s)
				n++;
			else if (*(ctr - 1) == c)
				n++;
			ctr++;
		}
	}
	return (n);
}

static char	*ft_findword(char const *s, char c, int *p)
{
	char	*word;
	int		i;
	int		j;
	int		size;

	i = *p;
	while (s[i] == c)
		i++;
	j = i;
	while (s[j] != c && s[j] != '\0')
		j++;
	size = j - i;
	word = ft_strnew(size);
	if (!word)
		return (NULL);
	word = ft_strncpy(word, &s[i], size);
	*p = j;
	return (word);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**result;
	int		numw;
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = 0;
	numw = ft_numwords(s, c);
	result = (char **)malloc(sizeof(char *) * numw + 1);
	if (!result)
		return (NULL);
	result[numw] = NULL;
	while (j < numw)
	{
		tmp = ft_findword(s, c, &i);
		if (!tmp)
		{
			ft_memdel((void **)&result);
			return (NULL);
		}
		result[j] = tmp;
		j++;
	}
	return (result);
}

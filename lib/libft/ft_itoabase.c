/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoabase.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 10:38:11 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/28 11:51:32 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_arrlen(int n, int base)
{
	int count;

	count = 1;
	if (n < 0)
	{
		if (base == 10)
			count++;
		n *= -1;
	}
	while (n >= base)
	{
		n /= base;
		count++;
	}
	return (count);
}

static void	ft_convert(int n, int base, char *s)
{
	char	c;
	int		i;

	i = 0;
	if (n >= base)
	{
		ft_convert(n / base, base, s);
		ft_convert(n % base, base, s);
	}
	else
	{
		c = n + '0';
		if (n > 9)
			c = c + 7;
		while (s[i] != 0)
			i++;
		s[i] = c;
	}
}

char		*ft_itoabase(int n, int base)
{
	int		len;
	char	*res;

	if (base < 2 || base > 16)
		return (NULL);
	if (n == -2147483648)
	{
		if (base == 10)
			return (ft_strdup("-2147483648"));
		return (NULL);
	}
	len = ft_arrlen(n, base);
	res = ft_strnew(len);
	if (!res)
		return (NULL);
	if (n < 0)
	{
		if (base == 10)
			res[0] = '-';
		n *= -1;
	}
	ft_convert(n, base, res);
	return (res);
}

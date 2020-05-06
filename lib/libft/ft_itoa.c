/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/25 12:24:22 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/28 09:15:42 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static char	*ft_intmax(void)
{
	char *result;

	result = ft_strdup("-2147483648");
	if (!result)
		return (NULL);
	return (result);
}

char		*ft_itoa(int n)
{
	char	*r;
	int		len;
	int		index;

	if (n == -2147483648)
		return (ft_intmax());
	len = ft_len(n);
	index = len - 1;
	r = ft_strnew(len);
	if (!r)
		return (NULL);
	if (n < 0)
	{
		r[0] = '-';
		n *= -1;
	}
	if (n == 0)
		*r = '0';
	while (n > 0)
	{
		r[index] = n % 10 + '0';
		n /= 10;
		index--;
	}
	return (r);
}

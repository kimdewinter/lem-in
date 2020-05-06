/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoibase.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 15:13:50 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/29 11:39:28 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_convchar(char c)
{
	int res;

	if (c >= 'a' && c <= 'f')
		res = c - 'a' + 10;
	else
		res = c - '0';
	return (res);
}

static int		ft_findstart(char *s, int *neg, int base)
{
	int i;

	i = 0;
	while (ft_isspace(s[i]))
		i++;
	while ((s[i] == '+' || s[i] == '-') && (ft_isdigit(s[i + 1]) ||
((s[i + 1] >= 'a' && (s[i + 1] < 'a' + base - 10)) && base > 10)))
	{
		if (s[i] == '-' && base == 10)
			*neg = 1;
		i++;
	}
	return (i);
}

static char		*ft_strsubatoi(char *s, int base)
{
	int		i;
	int		j;
	int		size;
	int		neg;
	char	*res;

	neg = 0;
	i = ft_findstart(s, &neg, base);
	j = i;
	while (ft_isdigit(s[j]) || ((s[j] >= 'a' && s[j] < 'a' + (base - 10)) &&
base > 10))
		j++;
	if (i >= j)
		return (res = ft_strdup(""));
	size = j - i;
	res = ft_strnew(size + neg);
	if (!res)
		return (NULL);
	ft_strncpy(res, &s[i - neg], size + neg);
	return (res);
}

static int		ft_convert(char *s, int base)
{
	int i;
	int neg;
	int result;
	int pow;

	neg = 0;
	result = 0;
	pow = 0;
	i = ft_strlen(s) - 1;
	if (s[0] == '-')
		neg = 1;
	while (i - neg >= 0)
	{
		result += ft_convchar(s[i]) * ft_pow(base, pow);
		i--;
		pow++;
	}
	return (result);
}

int				ft_atoibase(char *s, int base)
{
	char	*res;
	int		r;

	if (base < 2 || base > 16)
		return (-0);
	if (base == 10)
		return (ft_atoi(s));
	ft_strtolower(s);
	res = ft_strsubatoi(s, base);
	if (!res)
		return (-0);
	else if (ft_strcmp(res, "") == 0)
		return (-0);
	r = ft_convert(res, base);
	return (r);
}

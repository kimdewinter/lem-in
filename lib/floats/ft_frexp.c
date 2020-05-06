/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_frexp.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 16:10:36 by lravier        #+#    #+#                */
/*   Updated: 2019/11/09 14:25:26 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/floats.h"

static long int					get_exp(unsigned char *str)
{
	int			i;
	long int	res;
	long int	mask;

	mask = (1UL << 14);
	res = 0;
	i = 0;
	while (i < 15)
	{
		if (str[i] == '1')
			res |= mask;
		mask >>= 1;
		i++;
	}
	return (res - OFFSET);
}

static void						create_string(uint8_t *byte_pointer,
unsigned char *arr)
{
	int		index;
	int		ind;
	uint8_t	bit;
	uint8_t	byte;
	int		i;

	index = 10;
	while (index > 0)
	{
		bit = ARR;
		byte = byte_pointer[index - 1];
		i = 0;
		while (i < 8)
		{
			ind = ((9 - (index - 1)) * 8) + i;
			if (byte & bit)
				arr[ind] = '1';
			else
				arr[ind] = '0';
			bit >>= 1;
			i++;
		}
		index--;
	}
}

static unsigned char			*extract_bin(long double value)
{
	uint8_t			*byte_pointer;
	unsigned char	*arr;

	byte_pointer = (uint8_t *)&value;
	arr = (unsigned char *)malloc(10 * 8);
	if (!arr)
		return (NULL);
	create_string(byte_pointer, arr);
	return (arr);
}

static long long unsigned		str_to_u64(unsigned char *mant)
{
	unsigned long long	mask;
	unsigned long long	mnt;
	int					i;

	i = 0;
	mask = (1ULL << 63);
	mnt = 0ULL;
	while (i < 64)
	{
		if (mant[i] == '1')
			mnt |= mask;
		i++;
		mask >>= 1ULL;
	}
	return (mnt);
}

int								ft_frexp(long double n, long int *exp,
t_bigint *val, long long unsigned *mnt)
{
	unsigned char		*bin_rep;

	bin_rep = extract_bin(n);
	if (bin_rep)
	{
		val->sign = bin_rep[0] - '0';
		*mnt = str_to_u64(&bin_rep[16]);
		*exp = get_exp(&bin_rep[1]);
		free(bin_rep);
		return (1);
	}
	return (0);
}

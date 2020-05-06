/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_size_of_datatype.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 13:01:39 by lravier        #+#    #+#                */
/*   Updated: 2019/10/13 20:29:57 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

size_t	get_size_of_datatype2(char *datatype)
{
	if (ft_strcmp(datatype, US_INT) == 0)
		return (sizeof(unsigned short int));
	if (ft_strcmp(datatype, S_INT) == 0)
		return (sizeof(short int));
	if (ft_strcmp(datatype, L_INT) == 0)
		return (sizeof(long int));
	if (ft_strcmp(datatype, UL_INT) == 0)
		return (sizeof(unsigned long int));
	if (ft_strcmp(datatype, LL_INT) == 0)
		return (sizeof(long long int));
	if (ft_strcmp(datatype, ULL_INT) == 0)
		return (sizeof(unsigned long long int));
	if (ft_strcmp(datatype, DOUBLE) == 0)
		return (sizeof(double));
	if (ft_strcmp(datatype, L_DOUBLE) == 0)
		return (sizeof(long double));
	if (ft_strcmp(datatype, STRING) == 0)
		return (sizeof(const char *));
	if (ft_strcmp(datatype, V_POINT) == 0)
		return (sizeof(void *));
	else
		return (0);
}

size_t	get_size_of_datatype(char *datatype)
{
	if (ft_strcmp(datatype, INT) == 0)
		return (sizeof(int));
	if (ft_strcmp(datatype, U_INT) == 0)
		return (sizeof(unsigned int));
	if (ft_strcmp(datatype, U_CHAR) == 0)
		return (sizeof(unsigned char));
	if (ft_strcmp(datatype, W_INT) == 0)
		return (sizeof(wint_t));
	if (ft_strcmp(datatype, S_CHAR) == 0)
		return (sizeof(signed char));
	return (get_size_of_datatype2(datatype));
}

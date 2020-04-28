/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_working_data.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 13:03:40 by lravier        #+#    #+#                */
/*   Updated: 2019/10/13 21:18:44 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

long double	get_double(t_pf_arg *instr)
{
	long double d;

	if (instr->length_mods != 5)
		d = *(double *)instr->data;
	else
		d = *(long double *)instr->data;
	return ((long double)d);
}

intmax_t	get_number(t_pf_arg *instr)
{
	intmax_t num;

	if (ft_strcmp(instr->datatype, S_CHAR) == 0)
		num = *((signed char *)instr->data);
	else if (ft_strcmp(instr->datatype, S_INT) == 0)
		num = *((short int *)instr->data);
	else if (ft_strcmp(instr->datatype, L_INT) == 0)
		num = *((long int *)instr->data);
	else if (ft_strcmp(instr->datatype, LL_INT) == 0)
		num = *((long long int *)instr->data);
	else
		num = *((int *)instr->data);
	num = (intmax_t)num;
	return (num);
}

uintmax_t	get_unsigned_number(t_pf_arg *instr)
{
	uintmax_t num;

	if (ft_strcmp(instr->datatype, U_CHAR) == 0)
		num = *((unsigned char *)instr->data);
	else if (ft_strcmp(instr->datatype, US_INT) == 0)
		num = *((unsigned short int *)instr->data);
	else if (ft_strcmp(instr->datatype, UL_INT) == 0)
		num = *((unsigned long int *)instr->data);
	else if (ft_strcmp(instr->datatype, ULL_INT) == 0)
		num = *((unsigned long long int *)instr->data);
	else if (ft_strcmp(instr->datatype, V_POINT) == 0)
		num = *((unsigned long int *)instr->data);
	else
		num = *((unsigned int *)instr->data);
	num = (uintmax_t)num;
	return (num);
}

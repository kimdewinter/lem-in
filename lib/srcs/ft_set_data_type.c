/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_set_data_type.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 13:54:14 by lravier        #+#    #+#                */
/*   Updated: 2019/10/13 20:29:33 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static void		is_signed_int_conv(t_pf_arg *instr)
{
	if (instr->conversion == 'd' || instr->conversion == 'i')
	{
		if (instr->length_mods == 1)
			ft_strcpy(instr->datatype, S_CHAR);
		else if (instr->length_mods == 2)
			ft_strcpy(instr->datatype, S_INT);
		else if (instr->length_mods == 3)
			ft_strcpy(instr->datatype, L_INT);
		else if (instr->length_mods == 4)
			ft_strcpy(instr->datatype, LL_INT);
		else
			ft_strcpy(instr->datatype, INT);
	}
}

static void		is_unsigned_int_conv(t_pf_arg *instr)
{
	if (instr->conversion == 'o' || instr->conversion == 'u' ||
	instr->conversion == 'x' || instr->conversion == 'X' ||
	instr->conversion == 'b')
	{
		if (instr->length_mods == 1)
			ft_strcpy(instr->datatype, U_CHAR);
		else if (instr->length_mods == 2)
			ft_strcpy(instr->datatype, US_INT);
		else if (instr->length_mods == 3)
			ft_strcpy(instr->datatype, UL_INT);
		else if (instr->length_mods == 4)
			ft_strcpy(instr->datatype, ULL_INT);
		else
			ft_strcpy(instr->datatype, U_INT);
	}
}

static void		is_double_conv(t_pf_arg *instr)
{
	if (instr->conversion == 'e' || instr->conversion == 'E' ||
	instr->conversion == 'f' || instr->conversion == 'F' ||
	instr->conversion == 'g' || instr->conversion == 'G')
	{
		if (instr->length_mods == 5)
			ft_strcpy(instr->datatype, L_DOUBLE);
		else
			ft_strcpy(instr->datatype, DOUBLE);
	}
}

void			set_datatype(t_pf_arg *instr)
{
	is_signed_int_conv(instr);
	is_unsigned_int_conv(instr);
	is_double_conv(instr);
	if (instr->conversion == 'c')
	{
		if (instr->length_mods == 3)
			ft_strcpy(instr->datatype, W_INT);
		else
			ft_strcpy(instr->datatype, U_CHAR);
	}
	if (instr->conversion == 's')
		ft_strcpy(instr->datatype, STRING);
	if (instr->conversion == 'p')
		ft_strcpy(instr->datatype, V_POINT);
}

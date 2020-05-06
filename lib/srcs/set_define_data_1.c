/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_define_data_1.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 14:23:15 by lravier        #+#    #+#                */
/*   Updated: 2019/11/11 11:53:24 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

void	set_int(va_list args, t_pf_arg *tmp)
{
	int data;

	data = va_arg(args, int);
	ft_memcpy(tmp->data, &data, tmp->datasize);
}

void	set_uint(va_list args, t_pf_arg *tmp)
{
	unsigned int data;

	data = va_arg(args, unsigned int);
	ft_memcpy(tmp->data, &data, tmp->datasize);
}

void	set_uchar(va_list args, t_pf_arg *tmp)
{
	unsigned char data;

	data = va_arg(args, int);
	ft_memcpy(tmp->data, &data, tmp->datasize);
}

void	set_schar(va_list args, t_pf_arg *tmp)
{
	signed char data;

	data = va_arg(args, int);
	ft_memcpy(tmp->data, &data, tmp->datasize);
}

void	set_usint(va_list args, t_pf_arg *tmp)
{
	unsigned short int data;

	data = va_arg(args, int);
	ft_memcpy(tmp->data, &data, tmp->datasize);
}

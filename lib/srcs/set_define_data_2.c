/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_define_data_3.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 14:24:00 by lravier        #+#    #+#                */
/*   Updated: 2019/10/08 14:34:10 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

void	set_sint(va_list args, t_pf_arg *tmp)
{
	short int data;

	data = va_arg(args, int);
	ft_memcpy(tmp->data, &data, tmp->datasize);
}

void	set_lint(va_list args, t_pf_arg *tmp)
{
	long int data;

	data = va_arg(args, long int);
	ft_memcpy(tmp->data, &data, tmp->datasize);
}

void	set_ulint(va_list args, t_pf_arg *tmp)
{
	unsigned long int data;

	data = va_arg(args, unsigned long int);
	ft_memcpy(tmp->data, &data, tmp->datasize);
}

void	set_llint(va_list args, t_pf_arg *tmp)
{
	long long int data;

	data = va_arg(args, long long int);
	ft_memcpy(tmp->data, &data, tmp->datasize);
}

void	set_ullint(va_list args, t_pf_arg *tmp)
{
	unsigned long long int data;

	data = va_arg(args, unsigned long long int);
	ft_memcpy(tmp->data, &data, tmp->datasize);
}

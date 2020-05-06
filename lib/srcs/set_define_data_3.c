/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_define_data_3.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 14:24:36 by lravier        #+#    #+#                */
/*   Updated: 2019/11/09 20:23:05 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

void	set_double(va_list args, t_pf_arg *tmp)
{
	double data;

	data = va_arg(args, double);
	ft_memcpy(tmp->data, &data, tmp->datasize);
}

void	set_wint(va_list args, t_pf_arg *tmp)
{
	wint_t data;

	data = va_arg(args, wint_t);
	ft_memcpy(tmp->data, &data, tmp->datasize);
}

void	set_vpoint(va_list args, t_pf_arg *tmp)
{
	void *data;

	data = va_arg(args, void *);
	if (data)
		tmp->data = ft_memcpy(tmp->data, &data, tmp->datasize);
	else
	{
		ft_memdel(&tmp->data);
		tmp->datasize = 0;
	}
}

void	set_ldouble(va_list args, t_pf_arg *tmp)
{
	long double data;

	data = va_arg(args, long double);
	ft_memcpy(tmp->data, &data, tmp->datasize);
}

int		set_string(va_list args, t_pf_arg *tmp)
{
	char *data;

	data = va_arg(args, char *);
	tmp->data = ft_strdup(data);
	if (data)
		ft_strcpy(tmp->data, data);
	else
	{
		ft_memdel(&tmp->data);
		tmp->datasize = 0;
	}
	return (1);
}

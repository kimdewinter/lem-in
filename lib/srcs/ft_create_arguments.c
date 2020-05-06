/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_create_arguments.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/07 11:42:19 by lravier        #+#    #+#                */
/*   Updated: 2019/11/14 13:31:57 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static int		conv_no_i(va_list curr, va_list prev, int *dbl, t_pf_arg *tmp)
{
	if (*dbl != 0)
	{
		va_copy(curr, prev);
		ft_set_data(curr, tmp);
	}
	else
	{
		*dbl += 1;
		va_copy(prev, curr);
		ft_set_data(curr, tmp);
	}
	return (1);
}

static int		fw_no_i(va_list curr, va_list prev, int *dbl, t_pf_arg *tmp)
{
	if (*dbl != 0)
	{
		va_copy(curr, prev);
		tmp->field_width = va_arg(curr, int);
	}
	else
	{
		*dbl += 1;
		va_copy(prev, curr);
		tmp->field_width = va_arg(curr, int);
	}
	return (1);
}

static int		prec_no_i(va_list curr, va_list prev, int *dbl, t_pf_arg *tmp)
{
	if (*dbl != 0)
	{
		va_copy(curr, prev);
		tmp->precision = va_arg(curr, int);
	}
	else
	{
		*dbl += 1;
		va_copy(prev, curr);
		tmp->precision = va_arg(curr, int);
	}
	return (1);
}

static void		get_argument_values(t_pf_arg **instructions,
va_list args, int *range, int high)
{
	t_pf_arg	*tmp;
	va_list		prev;
	int			dbl;
	int			i;

	i = 1;
	va_copy(prev, args);
	while (i <= high)
	{
		dbl = 0;
		tmp = *instructions;
		while (tmp && (range[i - 1] != dbl))
		{
			if (tmp->conv_no == i)
				conv_no_i(args, prev, &dbl, tmp);
			if (tmp->fw_no == i)
				fw_no_i(args, prev, &dbl, tmp);
			if (tmp->prec_no == i)
				prec_no_i(args, prev, &dbl, tmp);
			tmp = tmp->next;
		}
		check_double(dbl, args);
		i++;
	}
	va_end(prev);
}

int				ft_create_arguments(t_pf_arg **instructions,
va_list args)
{
	int high;
	int *range;

	high = 0;
	find_highest(instructions, &high);
	range = (int *)malloc(sizeof(int) * high);
	if (!range)
		return (0);
	check_range(instructions, high, range);
	get_argument_values(instructions, args, range, high);
	free(range);
	if (!adjust_flags_precision(instructions))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vsprintf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 14:25:56 by lravier        #+#    #+#                */
/*   Updated: 2019/11/11 12:40:10 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static t_writer		*initialize_wrt(char *s)
{
	t_writer *wrt;

	wrt = (t_writer *)malloc(sizeof(t_writer));
	if (!wrt)
		return (NULL);
	wrt->curr = 0;
	wrt->u.vsn.str = s;
	wrt->ft_write = &ft_write_vs;
	return (wrt);
}

int					ft_vsprintf(char *str,
const char *format, va_list ap)
{
	t_pf_arg	*instructions;
	t_writer	*wrt;
	int			res;

	if (!str || !format)
		return (-1);
	wrt = initialize_wrt(str);
	if (!wrt)
		return (-1);
	instructions = NULL;
	if (!ft_parse_format(format, &instructions))
		return (-1);
	if (!ft_create_arguments(&instructions, ap))
		return (-1);
	if (!ft_dispatcher(&instructions, format, wrt))
		return (-1);
	res = wrt->curr;
	str[wrt->curr] = '\0';
	free(wrt);
	return (res);
}

int					ft_sprintf(char *str,
const char *format, ...)
{
	va_list ap;
	int		res;

	va_start(ap, format);
	res = ft_vsprintf(str, format, ap);
	va_end(ap);
	return (res);
}

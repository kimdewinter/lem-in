/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vfprintf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 11:07:17 by lravier        #+#    #+#                */
/*   Updated: 2019/11/11 12:41:08 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static t_writer		*initialize_wrt(FILE *stream)
{
	t_writer *wrt;

	wrt = (t_writer *)malloc(sizeof(t_writer));
	if (!wrt)
		return (NULL);
	wrt->curr = 0;
	wrt->len = 0;
	wrt->u.vf.fp = stream;
	wrt->ft_write = &ft_write_vf;
	return (wrt);
}

int					ft_vfprintf(FILE *stream,
const char *format, va_list ap)
{
	t_pf_arg	*instructions;
	t_writer	*wrt;
	int			res;

	if (!format || !stream)
		return (-1);
	wrt = initialize_wrt(stream);
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
	free(wrt);
	return (res);
}

int					ft_fprintf(FILE *stream,
const char *format, ...)
{
	va_list ap;
	int		res;

	va_start(ap, format);
	res = ft_vfprintf(stream, format, ap);
	va_end(ap);
	return (res);
}

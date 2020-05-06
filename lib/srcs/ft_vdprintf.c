/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vdprintf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 11:07:17 by lravier        #+#    #+#                */
/*   Updated: 2019/11/14 13:17:47 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static t_writer		*initialize_wrt(int fd)
{
	t_writer *wrt;

	wrt = (t_writer *)malloc(sizeof(t_writer));
	if (!wrt)
		return (NULL);
	wrt->curr = 0;
	wrt->len = 0;
	wrt->u.vd.fd = fd;
	(wrt->ft_write) = &ft_write_vd;
	return (wrt);
}

int					ft_vdprintf(int fd, const char *format,
va_list ap)
{
	t_pf_arg	*instructions;
	t_writer	*wrt;
	int			res;

	if (!format || fd < 0)
		return (-1);
	instructions = NULL;
	wrt = initialize_wrt(fd);
	if (!wrt)
		return (-1);
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

int					ft_printf(const char *format, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, format);
	res = ft_vdprintf(1, format, ap);
	va_end(ap);
	return (res);
}

int					ft_dprintf(int fd, const char *format, ...)
{
	va_list ap;
	int		res;

	va_start(ap, format);
	res = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (res);
}

int					ft_vprintf(const char *format, va_list ap)
{
	return (ft_vdprintf(1, format, ap));
}

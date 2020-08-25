/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vsnprintf.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 11:07:17 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/25 17:11:20 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static t_writer		*initialize_wrt(size_t size, char *str)
{
	t_writer *wrt;

	wrt = (t_writer *)malloc(sizeof(t_writer));
	if (!wrt)
		return (NULL);
	wrt->curr = 0;
	wrt->len = 0;
	wrt->u.vsn.vsn_max = size;
	wrt->u.vsn.last_ind = 0;
	wrt->u.vsn.str = str;
	if (size != 0)
		wrt->u.vsn.space = 1;
	else
		wrt->u.vsn.space = 0;
	wrt->ft_write = &ft_write_vsn;
	return (wrt);
}

int					ft_vsnprintf(char *str, size_t size,
const char *format, va_list ap)
{
	t_pf_arg	*instructions;
	t_writer	*wrt;
	int			res;

	if (!format || !str)
		return (-1);
	wrt = initialize_wrt(size, str);
	if (!wrt)
		return (-1);
	instructions = NULL;
	if (!ft_parse_format(format, &instructions))
		return (-1);
	if (!ft_create_arguments(&instructions, ap))
		return (-1);
	if (!ft_dispatcher(&instructions, format, wrt))
		return (-1);
	if (wrt->u.vsn.vsn_max != 0)
		str[wrt->u.vsn.last_ind] = '\0';
	res = wrt->curr;
	free(wrt);
	return (res);
}

int					ft_snprintf(char *str, size_t size,
const char *format, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, format);
	res = ft_vsnprintf(str, size, format, ap);
	va_end(ap);
	return (res);
}

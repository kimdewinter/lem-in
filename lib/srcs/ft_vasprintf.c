/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vasprintf.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 11:07:17 by lravier        #+#    #+#                */
/*   Updated: 2019/11/14 13:37:45 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static t_writer		*initialize_wrt(char **ret)
{
	t_writer *wrt;

	wrt = (t_writer *)malloc(sizeof(t_writer));
	if (!wrt)
		return (NULL);
	wrt->curr = 0;
	wrt->len = 0;
	wrt->u.vas.cpp = ret;
	*ret = ft_strnew(BUFF_SIZE);
	if (!*ret)
		return (NULL);
	wrt->u.vas.vas_size = BUFF_SIZE;
	wrt->ft_write = &ft_write_vas;
	return (wrt);
}

static int			ft_trim_string(char **ret, t_writer *wrt)
{
	char	*tmp;
	char	*prev;

	prev = *ret;
	tmp = ft_strnew(wrt->curr);
	if (!tmp)
		return (0);
	ft_strncpy(tmp, *ret, wrt->curr);
	if (prev)
		free(prev);
	*ret = tmp;
	return (1);
}

static int			ft_get_arguments(const char *format, t_pf_arg *instructions,
va_list ap)
{
	if (!ft_parse_format(format, &instructions))
		return (0);
	if (!ft_create_arguments(&instructions, ap))
		return (0);
	return (1);
}

int					ft_vasprintf(char **ret, const char *format,
va_list ap)
{
	t_pf_arg	*instructions;
	t_writer	*wrt;
	int			res;

	if (!format)
		return (-1);
	wrt = initialize_wrt(ret);
	if (!wrt)
		return (-1);
	instructions = NULL;
	if (!ft_get_arguments(format, instructions, ap))
		return (-1);
	if (!ft_dispatcher(&instructions, format, wrt))
	{
		*ret = NULL;
		return (-1);
	}
	if (wrt->u.vas.vas_size != 0)
	{
		if (!ft_trim_string(ret, wrt))
			return (-1);
	}
	res = wrt->curr;
	free(wrt);
	return (res);
}

int					ft_asprintf(char **ret, const char *format, ...)
{
	va_list ap;
	int		res;

	va_start(ap, format);
	res = ft_vasprintf(ret, format, ap);
	va_end(ap);
	return (res);
}

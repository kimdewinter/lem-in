/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_writeout.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 14:20:12 by lravier        #+#    #+#                */
/*   Updated: 2019/11/14 13:22:12 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

int		ft_write_vs(char *src, int len, t_writer *wrt)
{
	if (len == 0)
		return (1);
	ft_strncpy(&(wrt->u.vsn.str[wrt->curr]), src, len);
	wrt->curr += len;
	return (1);
}

int		ft_write_vsn(char *src, int len, t_writer *wrt)
{
	int to_write;

	to_write = 0;
	if (len == 0)
		return (1);
	if (wrt->u.vsn.space)
	{
		if (wrt->curr + len >= (wrt->u.vsn.vsn_max - 1))
		{
			to_write = (wrt->u.vsn.vsn_max - 1) - wrt->curr;
			wrt->u.vsn.space = 0;
			wrt->u.vsn.last_ind = wrt->curr + to_write;
		}
		else
			to_write = len;
		ft_strncpy(&(wrt->u.vsn.str[wrt->curr]), src, to_write);
	}
	wrt->curr += len;
	return (1);
}

int		ft_write_vf(char *src, int len, t_writer *wrt)
{
	if (len == 0)
		return (1);
	if ((int)fwrite(src, 1, len, wrt->u.vf.fp) != len)
		return (0);
	wrt->curr += len;
	return (1);
}

int		ft_write_vd(char *src, int len, t_writer *wrt)
{
	if (len == 0)
		return (1);
	if (write(wrt->u.vd.fd, src, len) != len)
		return (0);
	wrt->curr += len;
	return (1);
}

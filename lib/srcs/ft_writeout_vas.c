/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_writeout_vas.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 13:20:17 by lravier        #+#    #+#                */
/*   Updated: 2019/11/14 13:20:49 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

int		ft_enlarge(char **str, int prev_size, int new_size)
{
	char *new;

	if (new_size - prev_size <= 0)
		return (1);
	new = ft_strnew((size_t)new_size);
	if (!new)
		return (0);
	ft_strcpy(new, *str);
	free(*str);
	*str = new;
	return (1);
}

int		ft_write_vas(char *src, int len, t_writer *wrt)
{
	int enlarge;

	if (len == 0)
		return (1);
	enlarge = wrt->u.vas.vas_size;
	if ((wrt->curr + len) >= (wrt->u.vas.vas_size - 1))
	{
		while (wrt->curr + len >= (enlarge - 1))
			enlarge += BUFF_SIZE;
		if (!ft_enlarge(wrt->u.vas.cpp, wrt->u.vas.vas_size,
		enlarge))
			return (0);
		wrt->u.vas.cpp = (char **)wrt->u.vas.cpp;
		wrt->u.vas.vas_size = enlarge;
	}
	ft_strncpy(&(*wrt->u.vas.cpp)[wrt->curr], src, len);
	wrt->curr += len;
	return (1);
}

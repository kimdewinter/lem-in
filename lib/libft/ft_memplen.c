/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memplen.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/04 15:09:37 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/25 17:11:20 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memplen(void *src, void *tofind, size_t len)
{
	size_t			i;
	unsigned char	*s;

	s = (unsigned char *)src;
	i = 0;
	while (&s[i] != tofind && i < len)
		i++;
	return (i);
}

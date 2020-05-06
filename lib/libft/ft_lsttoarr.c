/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lsttoarr.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/13 14:46:51 by lravier       #+#    #+#                 */
/*   Updated: 2019/04/16 16:15:35 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lsttoarr(t_list **lst, void **arr, size_t arrlen)
{
	t_list			*tmp;
	size_t			j;
	unsigned char	*p;
	unsigned char	*s;

	*arr = ft_memalloc(arrlen);
	s = (unsigned char *)*arr;
	tmp = *lst;
	if (arrlen == 0)
		return (0);
	while (tmp)
	{
		j = arrlen - tmp->content_size;
		p = (unsigned char *)tmp->content;
		ft_memcpy(&s[j], p, tmp->content_size);
		arrlen -= tmp->content_size;
		tmp = tmp->next;
	}
	return (1);
}

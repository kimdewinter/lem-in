/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstaddend.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/25 16:00:42 by lravier        #+#    #+#                */
/*   Updated: 2020/02/17 21:26:39 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstaddend(t_list **begin_list, void const *s, size_t n)
{
	t_list *new;
	t_list *tmp;

	tmp = *begin_list;
	new = ft_lstnew(s, n);
	if (!new)
		return (0);
	if (*begin_list == NULL)
		*begin_list = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

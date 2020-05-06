/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/25 16:46:59 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/27 17:56:08 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *result;
	t_list *last;

	result = f(lst);
	if (!result)
		return (NULL);
	last = result;
	while (lst->next)
	{
		lst = lst->next;
		last->next = f(lst);
		if (!last->next)
			return (NULL);
		last = last->next;
	}
	return (result);
}

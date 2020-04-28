/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstremove.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/31 17:17:13 by lravier       #+#    #+#                 */
/*   Updated: 2019/04/01 09:52:20 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremove(t_list **lst, t_list *elem, void (*del)(void *, size_t))
{
	t_list *curr;
	t_list *prev;

	curr = *lst;
	prev = curr;
	if (curr == elem)
	{
		if (curr->next)
		{
			*lst = curr->next;
			ft_lstdelone(&curr, del);
		}
		else
			ft_lstdel(lst, del);
		return ;
	}
	while (curr && curr != elem)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	prev->next = curr->next;
	ft_lstdelone(&curr, del);
}

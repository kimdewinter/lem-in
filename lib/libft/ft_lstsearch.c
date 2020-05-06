/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsearch.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/01 09:04:25 by lravier       #+#    #+#                 */
/*   Updated: 2019/04/11 12:46:38 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstsearch(t_list **lst, t_list *(*find)(t_list *, void *),
void *key)
{
	t_list *curr;

	curr = *lst;
	while (curr)
	{
		if (find(curr, key))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

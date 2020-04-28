/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstpopend.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/29 13:56:51 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/29 14:03:07 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpopend(t_list **lst)
{
	t_list *tmp;
	t_list *last;

	tmp = *lst;
	if (!tmp)
		return (NULL);
	while (tmp->next->next)
		tmp = tmp->next;
	last = tmp->next;
	tmp->next = NULL;
	return (last);
}

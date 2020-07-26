/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstpop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/29 13:32:02 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/29 13:46:19 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop(t_list **lst)
{
	t_list *tmp;

	tmp = *lst;
	if (!tmp)
		return (NULL);
	if (!tmp->next)
	{
		*lst = NULL;
		return (tmp);
	}
	else
	{
		*lst = tmp->next;
		tmp->next = NULL;
		return (tmp);
	}
}

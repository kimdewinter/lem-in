/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lsteremove.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 09:28:44 by lravier       #+#    #+#                 */
/*   Updated: 2019/04/11 13:00:20 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_relink(t_list *tmp, t_list *curr)
{
	t_list *prev;

	while (tmp && tmp != curr)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		prev->next = curr->next;
		ft_memdel((void **)&curr->content);
		ft_memdel((void **)&curr);
	}
}

void		ft_lsteremove(t_list **lst, t_list *curr)
{
	t_list *tmp;

	tmp = *lst;
	if (tmp == curr)
	{
		if (curr->next)
		{
			*lst = curr->next;
			ft_memdel((void **)&curr->content);
			ft_memdel((void **)curr);
		}
		else
		{
			ft_memdel((void **)&(*lst)->content);
			ft_memdel((void **)lst);
		}
	}
	else
		ft_relink(tmp, curr);
}

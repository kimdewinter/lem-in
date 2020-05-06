/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdel.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/25 15:14:54 by lravier       #+#    #+#                 */
/*   Updated: 2019/03/25 15:58:41 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del) (void *, size_t))
{
	t_list *curr;
	t_list *nxt;

	nxt = *alst;
	while (nxt)
	{
		curr = nxt;
		del(curr->content, curr->content_size);
		nxt = curr->next;
		free(curr);
	}
	*alst = NULL;
}

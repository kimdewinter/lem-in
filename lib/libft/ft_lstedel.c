/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstedel.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/16 10:47:39 by lravier       #+#    #+#                 */
/*   Updated: 2019/04/16 10:48:36 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstedel(t_list **alst)
{
	t_list *curr;
	t_list *nxt;

	nxt = *alst;
	while (nxt)
	{
		curr = nxt;
		free(curr->content);
		nxt = curr->next;
		free(curr);
	}
	*alst = NULL;
}

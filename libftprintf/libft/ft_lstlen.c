/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/29 13:22:33 by lravier       #+#    #+#                 */
/*   Updated: 2019/04/16 18:43:13 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstlen(t_list **lst)
{
	t_list	*tmp;
	int		count;

	count = 0;
	tmp = *lst;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

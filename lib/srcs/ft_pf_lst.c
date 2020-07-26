/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pf_lst.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 13:39:23 by lravier        #+#    #+#                */
/*   Updated: 2019/10/08 13:40:19 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

void	ft_pflstaddend(t_pf_arg *elem, t_pf_arg **instructions)
{
	t_pf_arg *tmp;

	tmp = *instructions;
	if (tmp == NULL)
		*instructions = elem;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
	}
}

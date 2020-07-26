/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/25 13:55:52 by lravier        #+#    #+#                */
/*   Updated: 2020/02/17 21:52:22 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*elem;
	void	*data;

	elem = (t_list *)malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	if (content == NULL)
	{
		elem->content_size = 0;
		elem->content = NULL;
	}
	else
	{
		elem->content_size = content_size;
		data = (void *)malloc(content_size);
		if (!data)
		{
			free(elem);
			return (NULL);
		}
		ft_memcpy(data, content, content_size);
		elem->content = data;
	}
	elem->next = NULL;
	return (elem);
}

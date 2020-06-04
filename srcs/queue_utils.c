/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 11:45:52 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/04 16:35:35 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

t_list			*ft_lstnew_no_malloc(void *content, size_t size)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new)
	{
		new->content_size = size;
		new->next = NULL;
		new->content = malloc(size);
		new->content = content;
		return (new);
	}
	return (NULL);
}

void			ft_lstaddend_no_alloc(t_qwrap *lst, t_list *new)
{
	t_list	*tmp;

	tmp = lst->last;
	if (tmp == NULL)
	{
		(*lst->queue) = new;
		lst->last = new;
	}
	else
	{
		tmp->next = new;
		lst->last = new;
	}
}

t_list	*new_queue_item(t_subpath *pt, t_room *dst, t_room *src)
{
	t_queue	*new;
	t_list	*node;

	new = (t_queue *)malloc(sizeof(t_queue));
	if (new)
	{
		new->new_conj = 0;
		new->dst = dst;
		new->src = src;
		new->path = pt;
		node = ft_lstnew_no_malloc(new, sizeof(t_queue *));
		if (!node)
			free (new);
	}
	return (node);
}

size_t		setup_queue(t_qwrap **queue, t_map *map)
{
	t_list	*new_node;
	size_t	i;

	i = 0;
	*queue = (t_qwrap *)malloc(sizeof(t_qwrap));
	if (!*queue)
		return (EXIT_FAILURE);
	(*queue)->last = NULL;
	(*queue)->queue = (t_list **)malloc(sizeof(t_list *));
	if (!(*queue)->queue)
		return (EXIT_FAILURE);
	(*(*queue)->queue) = NULL;
	if (map->end->sps == 1)
		return (EXIT_SUCCESS);
	while (i < map->end->neighbours_len)
	{
		new_node = new_queue_item((*map->end->routes),
		map->end->neighbours[i], map->end);
		if (!new_node)
			return (EXIT_FAILURE);
		ft_lstaddend_no_alloc(*queue, new_node);
		i++;
	}
	return (EXIT_SUCCESS);
}
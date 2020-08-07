/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_unnecessary_tubes_2.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 16:34:41 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/04 16:34:41 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_connection		*new_connection(t_connection *item)
{
	t_connection	*new;

	new = (t_connection *)malloc(sizeof(t_connection));
	if (new)
	{
		new->add = 1;
		new->src = item->src;
		new->src_nb = item->src_nb;
		new->dst = item->dst;
		new->dst_nb = item->dst_nb;
		new->dist = item->dist;
		new->prev = NULL;
		new->next = NULL;
		return (new);
	}
	return (NULL);
}

int				del_tube(t_room *from, t_room *to, t_map *map)
{
	int		found;
	int		ret;
	size_t	i;
	t_room 	*tmp;

	i = 0;
	found = 0;
	printf("From %s %lu to %s\n", from->name, from->neighbours_len, to->name);
	while (i < from->neighbours_len && found == 0)
	{
		if (from->neighbours[i] == to)
		{
			printf("Remove connection to %s from %s\n", from->neighbours[i]->name, from->name);
			if (from->neighbours_len == 1)
			{
				from->neighbours[i] = NULL;
				ret = 0;
			}
			else
			{
				tmp = from->neighbours[from->neighbours_len - 1];
				from->neighbours[from->neighbours_len - 1] = NULL;
				from->neighbours[i] = tmp;
				ret = 1;
			}
			found = 1;
		}
		i++;
	}
	printf("Found %d\n",found);
	if (found == 1)
	{
		from->neighbours_len--;
		if (from->neighbours_len == 2 && (from != map->start && from != map->end))
			from->is_junction = 0;
	}
	return (ret);
}

static void		find_next(t_connection *tmp, t_room **curr, t_room **nb,
int *found)
{
	if (*nb != tmp->dst_nb
	&& *nb != tmp->dst)
	{
		if ((*nb)->is_junction == 0)
		{
			*found = 1;
			tmp->dist++;
		}
		tmp->dst_nb = *curr;
		*curr = *nb;
	}
}

void		find_real_nb(t_room *src, t_connection *tmp, t_map *map)
{
	size_t	i;
	t_room	*nb;
	int		found;

	i = 0;
	nb = tmp->dst;
	found = 1;
	tmp->dist++;
	while (nb->is_junction == 0 && found == 1)
	{
		found = 0;
		i = 0;
		while (i < nb->neighbours_len)
		{
			if (nb->neighbours[i] != NULL)
			{
				find_next(tmp, &nb, &(nb->neighbours[i]), &found);
				if (found == 0 && nb->is_junction == 1)
				{
					break;
				}
			}
			i++;
		}
		if (found == 0 && nb->is_junction == 0)
		{
			tmp->dst = NULL;
			return ;
		}
	}
	// if (src == nb)
	// {
	// 	/* Can't this just be handled by the caller ??? */
	// 	printf("Rm find real nb\n");
	// 	del_tube(src, tmp->dst_nb, map);
	// }
	tmp->dst = nb;
}
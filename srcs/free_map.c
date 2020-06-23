/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 16:28:44 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/23 19:23:46 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

void		free_routes(t_subpath ***routes, size_t num_options)
{
	t_subpath	**tmp;
	size_t		i;

	i = 0;
	tmp = *routes;
	if (tmp)
	{
		while (i < num_options)
		{
			if (tmp[i])
			{
				if (tmp[i]->bitconj)
				{
					free (tmp[i]->bitconj);
					tmp[i]->bitconj = NULL;
				}
				if (tmp[i]->path)
				{
					free (tmp[i]->path);
					tmp[i]->path = NULL;
				}
			}
			i++;
		}
		free (tmp);
		tmp = NULL;
	}
}

void		free_room(t_room **room)
{
	t_room *tmp;

	tmp = *room;
	if (tmp)
	{
		free(tmp->neighbours);
		free_routes(&tmp->routes, tmp->num_options);
		if (tmp->bitconj)
			free (tmp->bitconj);
		if (tmp->name)
			free (name);
	}
}

void		free_entry(t_entry **entry)
{
	t_entry *tmp;

	tmp = *entry;
	if (tmp)
	{
		free_room(((t_room *)tmp->val));
	}
}

void		free_rooms(t_table **rooms)
{
	t_table *tmp;
	size_t	i;

	i = 0;
	if (rooms)
		tmp = *rooms;
	if (tmp)
	while (i < tmp->size)
	{
		if (tmp->entries[i])
			free_entry(&tmp->entries[i]);
		i++;
	}
}

void		free_map(t_map *map)
{
	free_rooms(&map->rooms);
}
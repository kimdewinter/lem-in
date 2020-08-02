/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bfs_directions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 13:37:28 by kim           #+#    #+#                 */
/*   Updated: 2020/07/31 16:22:20 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t			connect_neighbourhood(t_tube_vault *vault, t_room *src,
size_t index, const t_map *map)
{
	size_t	i;
	int		first;

	i = 0;
	first = 1;
	if (src == map->end)
	{
		vault->active_walkers--;
		vault->walkers[index] = NULL;
		return (EXIT_SUCCESS);
	}
	bite_add_room_to_bitfield(vault->visited, src, map);
	while (i < src->neighbours_len)
	{
		if (tube_exists(src, src->neighbours[i]) == 0)
		{
			if (add_tube(src, src->neighbours[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (first == 1)
			{
				vault->walkers[index] = src->neighbours[i];
				first = 0;
			}
			else
			{
				vault->walkers[vault->next_rnd_used] = src->neighbours[i];
				vault->next_rnd_used++;
				vault->active_walkers++;
			}
		}
		i++;
	}
	if (first == 1)
	{
		vault->active_walkers--;
		vault->walkers[index] = NULL;
	}
	return (EXIT_SUCCESS);
}

ssize_t			setup_tubes_vault(t_tube_vault *vault, const t_map *map)
{
	size_t	i;
	
	i = 0;
	vault->len = map->rooms->count;
	vault->used = 0;
	vault->active_walkers = 0;
	if (bite_alloc_noval(&vault->visited, map) == EXIT_FAILURE ||
		bite_bitroute_copy(vault->visited, map->start->bitroom, map) ==
		EXIT_FAILURE)
		return (EXIT_FAILURE);//add start room to visited
	vault->walkers = (t_room **)malloc(sizeof(t_room *) * vault->len);
	if (!vault->walkers)
		return (EXIT_FAILURE);
	while (i < map->start->neighbours_len)
	{
		vault->walkers[vault->used] = map->start->neighbours[i];
		vault->used++;
		vault->active_walkers++;
		i++;
	}
	vault->next_rnd_used = vault->used;
	return (EXIT_SUCCESS);
}

ssize_t			bfs_set_tubes(t_map *map)
{
	t_tube_vault	vault;
	size_t			i;

	if (setup_tubes_vault(&vault, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (vault.active_walkers > 0)
	{
		i = 0;
		while (i < vault.used)
		{
			if (vault.walkers[i] != NULL)
				if (connect_neighbourhood(&vault, vault.walkers[i], i, map) ==
					EXIT_FAILURE)
					return (EXIT_FAILURE);
			i++;
		}
		vault.used = vault.next_rnd_used;
	}
}

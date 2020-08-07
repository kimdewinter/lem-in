/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sanitize_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 16:41:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/07 10:36:06 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void		remove_dead_end_from_nbs(t_room *dead)
{
	size_t	i;
	size_t	j;
	size_t	len;
	t_room	*nb;
	t_room	*tmp;

	i = 0;
	while (i < dead->neighbours_len)
	{
		if (dead->neighbours[i] != NULL)
		{
			j = 0;
			nb = dead->neighbours[i];
			len = nb->neighbours_len;
			while (j < len)
			{
				if (nb->neighbours[j] == dead)
				{
					if (nb->neighbours_len == 1)
						nb->neighbours[j] = NULL;
					else
					{
						tmp = nb->neighbours[nb->neighbours_len - 1];
						nb->neighbours[nb->neighbours_len - 1] = NULL;
						nb->neighbours[j] = tmp;
					}
					nb->neighbours_len--;
					break;
				}
				j++;
			}
		}
		i++;
	}
}

static void		remove_dead_path(t_room **tmp, t_map *map)
{
	t_room	*prev;
	size_t	j;

	// (*tmp)->dead_end = 1;
	prev = *tmp;
	*tmp = *((*tmp)->neighbours);
	j = 0;
	while ((*tmp)->neighbours_len == 2 && *tmp != map->start
	&& *tmp != map->end)
	{
		j = 0;
		// (*tmp)->dead_end = 1;
		printf("dead end %s\n", (*tmp)->name);
		if ((*tmp)->neighbours[j] == prev)
			j++;
		prev = *tmp;
		*tmp = (*tmp)->neighbours[j];
	}
	remove_dead_end_from_nbs(prev);
}

static void		flag_conj(t_map *map)
{
	size_t	i;
	t_room	*tmp;

	i = 0;
	while (i < map->rooms->size)
	{
		if (map->rooms->entries[i] != NULL)
		{
			tmp = ((t_room *)map->rooms->entries[i]->val);
			if (tmp->neighbours_len > 2 || (tmp == map->start || tmp == map->end))
				tmp->is_junction = 1;
		}
		i++;
	}
}

static void		remove_dead_ends(t_map *map, int *changed)
{
	size_t	i;
	t_room	*tmp;

	i = 0;
	while (i < map->rooms->size)
	{
		if (map->rooms->entries[i] != NULL)
		{
			tmp = ((t_room *)map->rooms->entries[i]->val);
			if (tmp != map->start && tmp != map->end)
			{
				if (tmp->neighbours_len == 1)
				{
					*changed = 1;
					printf("Dead end %s\n", tmp->name);
					remove_dead_path(&tmp, map);
				}
			}
		}
		i++;
	}
}

ssize_t			sanitize_input(t_map *map)
{
	t_room *tmp;
	int		changed;

	printf("Sanitize input\n");
	changed = 1;
	if (map->rooms == NULL)
		return (parse_error(8));
	if (map->start == NULL)
		return (parse_error(9));
	if (map->end == NULL)
		return (parse_error(10));
	tmp = (t_room *)search_ht(map->rooms, map->start->name);
	if (tmp->neighbours == NULL)
		return (parse_error(11));
	tmp = (t_room *)search_ht(map->rooms, map->end->name);
	if (tmp->neighbours == NULL)
		return (parse_error(12));
	while (changed == 1)
	{
		changed = 0;
		remove_dead_ends(map, &changed);
		if (map->start->neighbours_len == 0 ||
			map->end->neighbours_len == 0)
		{
			printf("No connections from start or end\n");
			return (EXIT_FAILURE);
		}
		printf("\n\n		Changed after remove dead_ends %d\n\n\n", changed);
		flag_conj(map);
		printf("Before remove tubes\n");
		remove_unnecessary_tubes(map, &changed);
		flag_conj(map);
		printf("\n\n		Changed after remove un %d\n\n\n", changed);
	}
	print_map(map);
	exit (0);
	// if (map->start->neighbours_len == 0 ||
	// map->end->neighbours_len == 0)
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

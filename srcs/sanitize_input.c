/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sanitize_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 16:41:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/29 12:04:05 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

/* Needs checking:
	Is there a start room
	Is there an end room
*/

static void		remove_dead_ends(t_map *map)
{
	size_t	i;
	t_room	*prev;
	t_room	*tmp;
	size_t	j;
	size_t	dead_ends;

	j = 0;
	i = 0;
	dead_ends = 0;
	while (i < map->rooms->size)
	{
		if (map->rooms->entries[i] != NULL)
		{
			tmp = ((t_room *)map->rooms->entries[i]->val);
			if (tmp != map->start && tmp != map->end && tmp->dead_end == 0)
			{
				if (tmp->neighbours_len == 1)
				{
					tmp->dead_end = 1;
					dead_ends++;
					prev = tmp;
					tmp = (*tmp->neighbours)->nb;
					while (tmp->neighbours_len == 2 && tmp != map->start
					&& tmp != map->end)
					{
						j = 0;
						tmp->dead_end = 1;
						dead_ends++;
						if (tmp->neighbours[j]->nb == prev)
							j++;
						prev = tmp;
						tmp = tmp->neighbours[j]->nb;
					}
					tmp->viable_nbs--;
				}
			}
		}
		i++;
	}
	printf("Dead ends %lu\n", dead_ends);
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
			if (tmp->viable_nbs > 2 || (tmp->viable_nbs >= 2 &&
			(tmp == map->start || tmp == map->end)))
				tmp->is_conj = 1;
		}
		i++;
	}
}

// static void		viable_nbs_se(t_map *map)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	printf("Set viable nbs\n");
// 	while (i < map->start->neighbours_len)
// 	{
// 		j = 0;
// 		map->start->neighbours[i]->nb->viable_nbs = 0;
// 		while (j < map->start->neighbours[i]->nb->neighbours_len)
// 		{
// 			if (map->start->neighbours[i]->nb->neighbours[j]->nb->sps == 0
// 			&& map->start->neighbours[i]->nb->neighbours[j]->nb != map->start)
// 			{
// 				map->start->neighbours[i]->nb->viable_nbs++;
// 			}
// 			j++;
// 		}
// 		if (map->start->neighbours[i]->nb->viable_nbs == 0)
// 			map->start->neighbours[i]->nb->dead_end = 1;
// 		if (map->start->neighbours[i]->nb->viable_nbs == 1)
// 			map->start->neighbours[i]->nb->is_conj = 0;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < map->end->neighbours_len)
// 	{
// 		j = 0;
// 		map->end->neighbours[i]->nb->viable_nbs = 0;
// 		// printf("Curr: %s\n", map->end->neighbours[i]->nb->name);
// 		while (j < map->end->neighbours[i]->nb->neighbours_len)
// 		{
// 			if (map->end->neighbours[i]->nb->neighbours[j]->nb->spe == 0
// 			&& map->end->neighbours[i]->nb->neighbours[j]->nb != map->end)
// 			{
// 				map->end->neighbours[i]->nb->viable_nbs++;
// 				// printf("viable nb: %s\n", map->end->neighbours[i]->nb->neighbours[j]->nb->name);
// 			}
// 			j++;
// 		}
// 		if (map->end->neighbours[i]->nb->viable_nbs == 0)
// 			map->end->neighbours[i]->nb->dead_end = 1;
// 		if (map->end->neighbours[i]->nb->viable_nbs == 1)
// 			map->end->neighbours[i]->nb->is_conj = 0;
// 		i++;
// 	}
// }

static void		prepare_map(t_map *map)
{
	remove_dead_ends(map);
	flag_conj(map);
	// viable_nbs_se(map);
	// debug(map);
}

size_t			check_start_end(t_map *map)
{
	size_t	i;
	size_t	end;
	size_t	start;

	i = 0;
	end = 0;
	start = 0;
	while (i < map->end->neighbours_len)
	{
		if (map->end->neighbours[i]->nb->dead_end == 0)
		{
			end++;
			break;
		}
		i++;
	}
	i = 0;
	if (end == 0)
		return (EXIT_FAILURE);
	while (i < map->start->neighbours_len)
	{
		if (map->start->neighbours[i]->nb->dead_end == 0)
		{
			start++;
			break;
		}
		i++;
	}
	if (start == 0 || end == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

size_t			sanitize_input(t_map *map)
{
	t_room *tmp;

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
	prepare_map(map);
	return (check_start_end(map));
}

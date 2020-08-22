/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sanitize_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 16:41:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/22 16:25:16 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int					is_mutual_conn(t_room *curr, t_room *nb)
{
	size_t	i;

	i = 0;
	if (room_in_bitfield(curr, nb->unavailable) == 1)
		return (0);
	while (i < nb->neighbours_len)
	{
		if (nb->neighbours[i] == curr)
			return (1);
		i++;
	}
	return (0);
}

static void			flag_conj(t_map *map)
{
	size_t	i;
	t_room	*tmp;

	i = 0;
	while (i < map->rooms->size)
	{
		if (map->rooms->entries[i] != NULL)
		{
			tmp = ((t_room *)map->rooms->entries[i]->val);
			if (is_junction(tmp, map) == 1)
				tmp->is_junction = 1;
		}
		i++;
	}
}

static ssize_t		regular_checks(t_map *map)
{
	t_room	*tmp;

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
	return (1);
}

// void				update_unavailable(t_map *map)
// {
// 	size_t	i;
// 	size_t	j;
// 	t_room	*tmp;

// 	i = 0;
// 	j = 0;
// 	tmp = NULL;
// 	while (i < map->rooms->size)
// 	{
// 		if (map->rooms->entries[i] != NULL)
// 		{
// 			j = 0;
// 			tmp = ((t_room *)map->rooms->entries[i]->val);
// 			// printf("TMP %s %lu\n", tmp->name, tmp->neighbours_len);
// 			while (j < tmp->neighbours_len)
// 			{
// 				if (tmp->neighbours[j]->dist_to_start < tmp->dist_to_start
// 				&& room_in_bitfield(tmp->neighbours[j], tmp->unavailable) == 0)
// 					set_unavailable(tmp, tmp->neighbours[j], map);
// 				j++;
// 			}
// 		}
// 		i++;
// 	}
// }

ssize_t				sanitize_input(t_map *map)
{
	int		changed;
	size_t	res;
	int		round;

	round = 0;
	// print_map(map);
	changed = 1;
	res = regular_checks(map);
	if (res != 1)
		return (res);
	flag_conj(map);
	// remove_sps_spe_conns(map);
	// print_map(map);
	// exit (0);
	set_sps_spe_rooms(map);
	// remove_dead_ends(map, &changed);
	// set_weights(map, 1);
	// remove_sps_spe_conns(map);
	// print_map(map);
	// exit (0);
	while (changed > 0)
	{
		changed = 0;
		// update_unavailable(map);
		// // exit (0);
		// printf("BEFORE ROUND\n");
		// set_weights()
		// remove_sps_spe_conns(map);
		remove_dead_ends(map, &changed);
		// flag_conj(map);
		// set_weights(map, 1);
		// if (round == 2)
		// {
		// 	print_map(map);
		// 	printf("CHANGED %d\n", changed);
		// 	exit (0);
		// }
		// if (round == 2)
		// {
		// 	print_map(map);
		// 	exit (0);
		// }
		printf("\n\nAFTER DEAD ENDS %d\n\n", changed);
		// printf("\n\nAfter dead ends %d\n\n", changed);
		if (map->start->viable_nbs == 0 ||
			map->end->viable_nbs == 0)
		{
			printf("No connections start end\n");
			return (EXIT_FAILURE);
		}
		// flag_conj(map);
		remove_unnecessary_tubes(map, &changed);
		// if (round == 2)
		// {		
		// 	print_map(map);
		// 	exit (0);
		// }
		// print_map(map);
		// exit (0);
		printf("\n\nAfter rm unnecessary %d\n\n", changed);
		// flag_conj(map);
		round++;
		// printf("ROUND AFTER %d\n", round);
	}
	if (map->start->viable_nbs == 0 || map->end->viable_nbs == 0)
		return (EXIT_FAILURE);
	set_weights(map, -1);
	set_weights(map, 1);
	print_map(map);
	exit (0);
	return (EXIT_SUCCESS);
}

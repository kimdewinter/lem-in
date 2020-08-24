/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compare_candidate_sol.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 10:30:10 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/24 13:48:10 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void		delete_candidate(t_best *candidate)
{
	size_t	i;

	i = 0;
	while (i < candidate->used)
	{
		if (candidate->combi[i] != NULL)
		{
			free(candidate->combi[i]);
			candidate->combi[i] = NULL;
		}
		i++;
	}
	free(candidate->combi);
	free(candidate->in_paths);
	candidate->in_paths = NULL;
	candidate->combi = NULL;
	candidate->used = 0;
	candidate->len = 0;
	candidate->turns = 0;
	candidate->prev_turns = 0;
}

static void		replace_solution(t_map *map, t_best *candidate)
{
	delete_candidate(&map->solution);
	map->solution.combi = candidate->combi;
	map->solution.in_paths = candidate->in_paths;
	map->solution.len = candidate->len;
	map->solution.used = candidate->used;
	map->solution.prev_turns = candidate->prev_turns;
	map->solution.turns = candidate->turns;
}

void			compare_candidate_best(t_map *map, t_best *candidate)
{
	if (map->solution.combi == NULL)
	{
		map->solution.combi = candidate->combi;
		map->solution.in_paths = candidate->in_paths;
		map->solution.len = candidate->len;
		map->solution.turns = candidate->turns;
		map->solution.prev_turns = candidate->prev_turns;
		map->solution.used = candidate->used;
	}
	else if (candidate->turns < map->solution.turns)
		replace_solution(map, candidate);
	else
		delete_candidate(candidate);
}

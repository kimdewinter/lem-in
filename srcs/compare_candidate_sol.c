/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compare_candidate_sol.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 10:30:10 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/24 16:43:08 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void		replace_solution(t_map *map, t_best *candidate)
{
	delete_solution(&map->solution);
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
		delete_solution(candidate);
}

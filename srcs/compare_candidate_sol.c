/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compare_candidate_sol.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 10:30:10 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/17 13:30:05 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void		cleanup_candidate(t_best *candidate, size_t ants)
{
	size_t	i;

	i = ants;
	while (i < candidate->len && candidate->combi[i] != NULL)
	{
		if (candidate->combi[i] != NULL)
		{
			free(candidate->combi[i]);
			candidate->combi[i] = NULL;
			candidate->used--;
		}
		i++;
	}
}

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
	candidate->combi = NULL;
	candidate->used = 0;
	candidate->len = 0;
	candidate->turns = 0;
}

static void		replace_solution(t_map *map, t_best *candidate)
{
	delete_candidate(&map->solution);
	map->solution.combi = NULL;
	map->solution.combi = candidate->combi;
	map->solution.len = candidate->len;
	map->solution.used = candidate->used;
	map->solution.turns = candidate->turns;
}

void			compare_candidate_best(t_map *map, t_best *candidate)
{
	if (candidate->used > (size_t)map->antmount)
		cleanup_candidate(candidate, map->antmount);
	candidate->turns = calc_cost(map->antmount, candidate);
	if (map->solution.combi == NULL)
	{
		map->solution.combi = candidate->combi;
		map->solution.len = candidate->len;
		map->solution.turns = candidate->turns;
		map->solution.used = candidate->used;
	}
	else if (candidate->turns < map->solution.turns)
		replace_solution(map, candidate);
	else
		delete_candidate(candidate);
}

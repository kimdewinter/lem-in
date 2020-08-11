/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compare_state_sol.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/11 14:54:27 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/11 14:54:27 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void		cleanup_state(t_best *state, size_t ants)
{
	size_t	i;

	i = ants;
	while (i < state->len && state->combi[i] != NULL)
	{
		if (state->combi[i] != NULL)
		{
			free (state->combi[i]);
			state->combi[i] = NULL;
			state->used--;
		}
		i++;
	}
}

static void		delete_state(t_best *state)
{
	size_t	i;

	i = 0;
	while (i < state->used)
	{
		if (state->combi[i] != NULL)
		{
			free (state->combi[i]);
			state->combi[i] = NULL;
		}
		i++;
	}
	free (state->combi);
	state->combi = NULL;
	state->used = 0;
	state->len = 0;
	state->turns = 0;
}

static void		replace_solution(t_map *map, t_best *state)
{
	delete_state(&map->solution);
	map->solution.combi = NULL;
	map->solution.combi = state->combi;
	map->solution.len = state->len;
	map->solution.used = state->used;
	map->solution.turns = state->turns;
}

void			compare_state_best(t_map *map, t_best *state)
{
	if (state->used > (size_t)map->antmount)
		cleanup_state(state, map->antmount);
	state->turns = calc_cost(map->antmount, state);
	if (map->solution.combi == NULL)
	{
		map->solution.combi = state->combi;
		map->solution.len = state->len;
		map->solution.turns = state->turns;
		map->solution.used = state->used;
	}
	else if (state->turns < map->solution.turns)
		replace_solution(map, state);
	else
		delete_state(state);
}
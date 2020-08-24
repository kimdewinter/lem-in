/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_cost_add_path.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 13:44:07 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/24 13:47:37 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static long double	calc_paths_avg_add_path(const t_best *candidate,
t_route *route)
{
	size_t		i;
	long double total;

	i = 0;
	total = 0.0;
	while (i < candidate->used)
	{
		total += (long double)candidate->combi[i]->used;
		i++;
	}
	total += (long double)route->used;
	return (total / (long double)(candidate->used + 1));
}

static size_t		calc_rounds_add_path(long double *rest,
								long double avg_ants,
								const t_best *combi,
								t_route *route)
{
	long double path_diff;
	long double	ants;
	long double rounds;
	long double avg_paths;
	size_t		i;

	rounds = 0;
	i = 0;
	avg_paths = calc_paths_avg_add_path(combi, route);
	while (i < combi->used)
	{
		path_diff = (long double)combi->combi[i]->used - avg_paths;
		ants = avg_ants - path_diff;
		rounds = (long double)combi->combi[i]->used + ants - 1.0;
		*rest += (rounds - (size_t)rounds);
		i++;
	}
	path_diff = (long double)route->used - avg_paths;
	ants = avg_ants - path_diff;
	rounds = (long double)route->used + ants - 1.0;
	*rest += (rounds - (size_t)rounds);
	return (rounds + ft_round_rest(*rest));
}

size_t				calc_cost_add_route(const t_best *candidate, t_route *route,
t_map *map)
{
	long double avg_ants;
	long double rest;

	rest = 0.0;
	avg_ants = (long double)map->antmount /
	((long double)candidate->used + 1.0);
	return (calc_rounds_add_path(&rest, avg_ants, candidate, route));
}

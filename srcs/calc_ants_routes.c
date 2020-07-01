/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_ants_routes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 10:44:07 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/01 13:24:52 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t			calc_missed_ants(long double rest)
{
	size_t		fact;
	long double	rem;

	fact = (size_t)rest;
	rem = rest - fact;
	if (rem > 0.5)
		fact += 1;
	return (fact);
}

static size_t	calc_ants(long double *rest,
							long double avg_ants,
							long double avg_paths,
							const t_best *combi)
{
	long double path_diff;
	long double	ants_diff;
	long double rounds;
	size_t		i;

	i = 0;
	while (i < combi->used)
	{
		path_diff = (long double)combi->combi[i]->len - avg_paths;
		ants_diff = avg_ants - path_diff;
		rounds = (long double)combi->combi[i]->len + ants_diff - 1.0;
		combi->combi[i]->ants = (size_t)ants_diff;
		*rest += (rounds - (size_t)rounds);
		i++;
	}
	return (calc_missed_ants(*rest));
}

static void	divide_left_ants(t_best *combi, size_t ants_left)
{
	size_t	i;

	i = 0;
	while (i < ants_left)
	{
		combi->combi[i]->ants += 1;
		i++;
	}
}

static long double		calc_ants_avg(size_t ants, size_t num_paths)
{
	long double	result;

	result = (long double)ants / (long double)num_paths;
	return (result);
}

static long double		calc_paths_avg(size_t num_paths, const t_best *combi)
{
	size_t		i;
	long double total;

	i = 0;
	total = 0.0;
	while (i < num_paths)
	{
		total += (long double)combi->combi[i]->len;
		i++;
	}
	return (total / (long double)num_paths);
}

void		calculate_ants_per_path(size_t ants, t_best *best)
{
	long double avg_ants;
	long double avg_paths;
	long double rest;
	size_t		ants_left;

	rest = 0.0;
	avg_paths = calc_paths_avg(best->used, best);
	avg_ants = calc_ants_avg(ants, best->used);
	ants_left = calc_ants(&rest, avg_ants, avg_paths, best);
	divide_left_ants(best, ants_left);
}
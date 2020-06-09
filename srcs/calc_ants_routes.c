/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_ants_routes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 10:44:07 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/09 11:44:29 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

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

static size_t	calc_ants(long double *rest, long double avg_ants, long double
avg_paths, const t_poscom *combi)
{
	long double path_diff;
	long double	ants_diff;
	long double rounds;
	size_t		i;

	i = 0;
	while (i < combi->num_routes)
	{
		path_diff = (long double)combi->routes[i]->len - avg_paths;
		ants_diff = avg_ants - path_diff;
		rounds = (long double)combi->routes[i]->len + ants_diff - 1.0;
		combi->routes[i]->ants = (size_t)ants_diff;
		*rest += (rounds - (size_t)rounds);
		i++;
	}
	return (calc_missed_ants(*rest));
}

void		calculate_ants_per_path(size_t ants, size_t *ants_left,
t_poscom *best)
{
	long double avg_ants;
	long double avg_paths;
	long double rest;

	rest = 0.0;
	avg_paths = calc_paths_avg(best->num_routes, best);
	avg_ants = calc_ants_avg(ants, best->num_routes);
	*ants_left = calc_ants(&rest, avg_ants, avg_paths, best);
	printf("%lu\n", *ants_left);
}
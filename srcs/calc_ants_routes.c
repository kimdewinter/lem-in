/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_ants_routes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 10:44:07 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/09 10:52:14 by lravier       ########   odam.nl         */
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
		printf("Paths diff %Lf\n", path_diff);
		ants_diff = avg_ants - path_diff;
		printf("Ants diff %Lf\n", ants_diff);
		rounds = (long double)combi->routes[i]->len + ants_diff - 1.0;
		printf("Rounds %Lf\n\n", rounds);
		combi->routes[i]->ants = (size_t)ants_diff;
		printf("Ants on path: %ld\n", (size_t)ants_diff);
		*rest += (rounds - (size_t)rounds);
		i++;
	}
	return (calc_missed_ants(*rest));
}

void		calculate_ants_per_path(size_t ants, size_t *left_ants,
t_poscom *best)
{
	long double avg_ants;
	long double avg_paths;
	long double rest;

	rest = 0.0;
	avg_paths = calc_paths_avg(best->num_routes, best);
	avg_ants = calc_ants_avg(ants, best->num_routes);
	*left_ants = calc_ants(&rest, avg_ants, avg_paths, best);
	printf("%lu\n", *left_ants);
}
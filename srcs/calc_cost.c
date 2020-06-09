/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_cost.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/25 15:44:43 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/09 14:05:51 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static size_t			ft_round_rest(long double rest)
{
	size_t		fact;
	long double	rem;

	fact = (size_t)rest;
	rem = rest - fact;
	if (rem > 0.5)
		fact += 1;
	printf("Fact %ld\n", fact);
	if (fact > 0)
		return (1);
	return (0);
}

static long double		calc_ants_avg(size_t ants, size_t num_paths)
{
	long double	result;

	result = (long double)ants / (long double)num_paths;
	return (result);
}

static long double		calc_paths_avg(size_t num_paths, const t_poscom *routes)
{
	size_t		i;
	long double total;

	i = 0;
	total = 0.0;
	while (i < num_paths)
	{
		/* REMOVE - 1, THIS IS TEMPORARY FIX */
		total += (long double)routes->routes[i]->len;
		i++;
	}
	return (total / (long double)num_paths);
}

static size_t	calc_rounds(long double *rest, long double avg_ants, long double
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
		*rest += (rounds - (size_t)rounds);
		i++;
	}
	return (rounds + ft_round_rest(*rest));
}

size_t		calc_cost(size_t ants, const t_poscom *routes)
{
	long double avg_ants;
	long double	avg_paths;
	long double rest;
	size_t		result;

	rest = 0.0;
	printf("\nAnts: %lu\nRoutes:\n", ants);
	for (size_t i = 0; i < routes->num_routes; i++)
	{
		for (size_t j = 0; j < routes->routes[i]->len; j++)
			printf("%s ", routes->routes[i]->route[j]->name);
		printf("\n");
	}
	printf("\n");
	avg_ants = calc_ants_avg(ants, routes->num_routes);
	avg_paths = calc_paths_avg(routes->num_routes, routes);
	printf("Ants avg %Lf\nPaths avg %Lf\n", avg_ants, avg_paths);
	result = calc_rounds(&rest, avg_ants, avg_paths, routes);
	printf("Result %lu\n", result);
	printf("\n");
	return (result);
}
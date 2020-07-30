/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_cost.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/25 15:44:43 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/28 20:09:04 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t		ft_round_rest(long double rest)
{
	size_t		fact;
	long double	rem;

	fact = (size_t)rest;
	rem = rest - fact;
	if (rem > 0.5)
		fact += 1;
	if (fact > 0)
		return (1);
	return (0);
}

static long double	calc_ants_avg(size_t ants, size_t num_paths)
{
	long double	result;

	result = (long double)ants / (long double)num_paths;
	return (result);
}

static long double	calc_paths_avg(size_t num_paths, t_path_combi *routes)
{
	size_t		i;
	long double total;

	i = 0;
	total = 0.0;
	while (i < num_paths)
	{
		total += (long double)routes->paths[i]->len;
		i++;
	}
	return (total / (long double)num_paths);
}

static size_t		calc_rounds(long double *rest,
								long double avg_ants,
								long double avg_paths,
								t_path_combi *combi)
{
	long double path_diff;
	long double	ants;
	long double rounds;
	size_t		i;

	rounds = 0;
	i = 0;
	while (i < combi->num_paths)
	{
		path_diff = (long double)combi->paths[i]->len - avg_paths;
		ants = avg_ants - path_diff;
		rounds = (long double)combi->paths[i]->len + ants - 1.0;
		*rest += (rounds - (size_t)rounds);
		i++;
	}
	return (rounds + ft_round_rest(*rest));
}

size_t				calc_cost(size_t ants, t_path_combi *routes)
{
	long double avg_ants;
	long double	avg_paths;
	long double rest;
	size_t 		cost;

	// if (DEBUG_MODE == 1)
	// {
	// 	printf("num routes %lu\n", routes->num_routes);
	// 	size_t	i;
	// 	i = 0;
	// 	while (i < routes->num_routes)
	// 	{
	// 		print_route(routes->routes[i]);
	// 		i++;
	// 	}
	// 	printf("\n");
	// }
	if (ants == 1 || (routes->num_paths == 1 && routes->paths[0]->len == 1))
		return (1);
	rest = 0.0;
	avg_ants = calc_ants_avg(ants, routes->num_paths);
	avg_paths = calc_paths_avg(routes->num_paths, routes);
	cost = calc_rounds(&rest, avg_ants, avg_paths, routes);
	return (cost);
}

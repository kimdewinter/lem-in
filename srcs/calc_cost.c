/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_cost.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/25 15:44:43 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/25 15:56:01 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

/* KEEP TRACK OF OVERFLOW!!! */
static size_t			ft_round_rest(long double rest)
{
	size_t		fact;
	long double	rem;

	fact = (long long)rest;
	rem = rest - fact;
	if (rem > 0.5)
	fact += 1;
	return (fact);
}

static long double		calc_ants_avg(ssize_t ants, size_t num_paths)
{
	long double	result;

	result = (long double)ants / (long double)num_paths;
	return (result);
}

static	long double		calc_paths_avg(size_t num_paths, va_list paths)
{
	ssize_t		i;
	t_route		*tmp;
	long double total;

	i = 0;
	while (i < num_paths)
	{
		tmp = va_arg(paths, t_route *);
		total += (long double)tmp->len;
		i++;
	}
	return (total / (long double)num_paths);
}

static size_t	calc_rounds(long double *rest, long double avg_ants, long double
avg_paths, t_combi *combi)
{
	long double path_diff;
	long double	ants_diff;
	long double rounds;
	t_route		*tmp;
	size_t		i;

	i = 0;
	while (i < combi->num_routes)
	{
		tmp = combi->routes[i];
		path_diff = (long double)tmp->len - avg_paths;
		ants_diff = avg_ants - path_diff;
		rounds = (long double)tmp->len + ants_diff - 1.0;
		/* CHECK THIS */
		if ((rounds - (size_t)rounds) > 0)
			*rest += (rounds - (size_t)rounds);
		i++;
	}
	return (rounds + ft_round_rest(*rest));
}

size_t		calc_cost(ssize_t ants, t_combi *routes)
{
	long double avg_ants;
	long double	avg_paths;
	long double rest;
	va_list		paths;
	va_list		paths_cpy;

	rest = 0.0;
	avg_ants = calc_ants_avg(ants, routes->num_routes);
	avg_paths = calc_paths_avg(routes->num_routes, routes);
	calc_rounds(&rest, avg_ants, avg_paths, routes);
}
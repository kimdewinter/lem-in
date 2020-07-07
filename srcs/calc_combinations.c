/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_combinations.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/22 16:03:32 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/07 14:15:00 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t	ft_factorial(size_t n)
{
	if (n == 0)
		return (1);
	return (n * ft_factorial(n - 1));
}

// N = number of paths, r is max number of parallel paths

long long unsigned			calc_combinations(const size_t n, size_t r)
{
	long long unsigned	result;
	long long unsigned	fact_n;

	// (n!) / (r!(n-r)!);
	result = 0;
	fact_n = ft_factorial(n);
		result = (fact_n / (ft_factorial(r) * ft_factorial(n - r)));
	if (result == 0)
		result = INTMAX_MAX;
	return (result);
}

size_t			max_parallels(t_map *map)
{
	size_t	lowest;

	lowest = map->start->neighbours_len;
	if (map->end->neighbours_len < lowest)
		lowest = map->end->neighbours_len;
	if ((size_t)map->antmount < lowest)
		lowest = map->antmount;
	if (map->num_routes < lowest)
		lowest = map->num_routes;
	return (lowest);
}
/*
** either number of viable routes
** number of ends
** connections to start
** connections to end
*/

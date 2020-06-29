/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_combinations.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/22 16:03:32 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/29 20:11:54 by kim           ########   odam.nl         */
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

ssize_t			calc_combinations(const size_t n, size_t r)
{
	size_t	result;
	size_t	fact_n;
	size_t	i;

	// (n!) / (r!(n-r)!);
	result = 0;
	i = r;
	fact_n = ft_factorial(n);
	while (i > 0)
	{
		result += (fact_n / (ft_factorial(i) * ft_factorial(n - i)));
		i--;
	}
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

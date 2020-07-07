/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_combinations.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/22 16:03:32 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/07 14:29:56 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t	ft_factorial(long long unsigned *res, size_t n)
{
	unsigned long long num;
	unsigned long long prev;

	num = n;
	*res = 1;
	while (num > 0)
	{
		prev = *res;
		*res *= num;
		if (*res / num != prev)
			return (EXIT_FAILURE);
		num--;
	}
	return (EXIT_SUCCESS);
}

// N = number of paths, r is max number of parallel paths

ssize_t			calc_combinations(long long unsigned *result,
const size_t n, size_t r)
{
	long long unsigned	fact_n;
	long long unsigned	fact_r;
	long long unsigned	fact_nr;
	long long unsigned	div;

	fact_n = 0;
	fact_r = 0;
	fact_nr = 0;
	div = 0;
	if (ft_factorial(&fact_n, n) == EXIT_SUCCESS
	&& ft_factorial(&fact_r, r) == EXIT_SUCCESS
	&& ft_factorial(&fact_nr, n - r) == EXIT_SUCCESS)
	{
		div = fact_r * fact_nr;
		if (div / fact_nr != fact_r)
			return (EXIT_FAILURE);
		*result = fact_n / div;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

size_t			max_parallels(const t_map *map)
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

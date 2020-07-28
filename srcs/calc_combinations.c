/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_combinations.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/22 16:03:32 by lravier       #+#    #+#                 */
/*   Updated: 2020/07/28 13:46:52 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	ft_factorial(long long unsigned *res, size_t n)
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
									const size_t n,
									size_t r)
{
	long long unsigned	fact_n;
	long long unsigned	fact_r;
	long long unsigned	fact_nr;
	long long unsigned	div;

	fact_n = 0;
	fact_r = 0;
	fact_nr = 0;
	div = 0;
	if (r == 1)
    {
        *result = n;
        return (EXIT_SUCCESS);
    }
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

void			adjust_for_paths_through_junction(int **visited, size_t *result,
t_room *conj, const t_map *map)
{
	size_t	i;
	ssize_t	first_i;
	ssize_t	total;

	i = 0;
	first_i = -1;
	total = 0;
	while (i < map->num_routes)
	{
		if ((*visited)[i] == 0 &&
		room_in_bitfield(conj, map->routes[i]->bitroute) == 1)
		{
			total++;
			first_i = i;
			(*visited)[i] = 1;
		}
		i++;
	}
	if (total == 1)
		(*visited)[first_i] = 0;
	if (total != 0)
		*result -= (total - 1);
}

size_t			calculate_max_real_parallels(size_t *result, const t_map *map)
{
	size_t	i;
	t_room	*tmp;
	int		*visited;

	i = 0;
	visited = (int *)malloc(sizeof(int) * map->num_routes);
	if (!visited)
		return (EXIT_FAILURE);
	ft_bzero(visited, sizeof(int) * map->num_routes);
	tmp = NULL;
	while (i < map->rooms->size)
	{
		if (map->rooms->entries[i] != NULL)
		{
			tmp = ((t_room *)map->rooms->entries[i]->val);
			if (tmp->is_conj == 1 && tmp != map->end && tmp != map->start)
			{
				adjust_for_paths_through_junction(&visited, result, tmp, map);
			}
		}
		i++;
	}
	free (visited);
	return (EXIT_SUCCESS);
}

static size_t	start_nbs(const t_map *map)
{
	size_t	active;
	size_t	i;

	i = 0;
	active = 0;
	while (i < map->start->neighbours_len)
	{
		if (map->start->neighbours[i]->num_options != 0)
			active++;
		i++;
	}
	return (active);
}

ssize_t			max_parallels(size_t *lowest, const t_map *map)
{
	size_t	max_calculated;
	size_t	active_start_nbs;

	max_calculated = map->num_routes;
	active_start_nbs = 0;
	// set_viable_se(map);
	if (calculate_max_real_parallels(&max_calculated, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// printf("Max parallels real %lu\n", max_calculated);
	// printf("Start: %lu\nEnd: %lu\nAnts: %lu\n", map->start->viable_nbs,
	// map->end->viable_nbs, map->antmount);
	// exit (0);
	*lowest = max_calculated;
	if (DEBUG_MODE == 1)
		printf("max parallels calculated %lu\nend neighbours %lu\n", max_calculated,
	map->end->neighbours_len);
	active_start_nbs =  start_nbs(map);
	if (active_start_nbs < *lowest)
		*lowest = active_start_nbs;
	if (map->end->neighbours_len < *lowest)
		*lowest = map->end->neighbours_len;
	if ((size_t)map->antmount < *lowest)
		*lowest = map->antmount;
	if (map->num_routes < *lowest)
		*lowest = map->num_routes;
	return (EXIT_SUCCESS);
}
/*
** either number of viable routes
** number of ends
** connections to start
** connections to end
*/

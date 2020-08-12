/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   outputter.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 13:54:50 by kim           #+#    #+#                 */
/*   Updated: 2020/08/12 14:19:43 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"


void		execute_round(t_routeput **routes,
							const t_map *map,
							size_t *curr_ant)
{
	size_t	j;

	j = 0;
	while (j < map->solution.used)
	{
		if (routes[j]->finished == 0)
		{
			if (routes[j]->ants_received != map->solution.combi[j]->ants)
			{
				execute_route(routes[j], *curr_ant);
				(*curr_ant)++;
			}
			else
				execute_route(routes[j], 0);
			if (j + 1 < map->solution.used)
				ft_printf(" ");
		}
		j++;
	}
}

void		print_input(const t_input_reader *input)
{
	size_t	i;

	i = 0;
	while (i < input->num_lines)
	{
		ft_printf("%s\n", input->lines[i]);
		i++;
	}
	ft_printf("\n");
}

static ssize_t	copy_roomnames(char ***rooms, t_route *curr)
{
	size_t	i;

	i = 0;
	*rooms = (char **)malloc(sizeof(char *) * curr->used);
	if (*rooms == NULL)
		return (EXIT_FAILURE);
	while (i < curr->used)
	{
		(*rooms)[i] = curr->route[i]->name;
		i++;
	}
	return (EXIT_SUCCESS);
}

static ssize_t	setup_ants(size_t **ants, size_t len)
{
	size_t	i;

	i = 0;
	*ants = (size_t *)malloc(sizeof(size_t) * len);
	if (*ants == NULL)
		return (EXIT_FAILURE);
	while (i < len)
	{
		(*ants)[i] = 0;
		i++;
	}
	return (EXIT_SUCCESS);
}

static ssize_t	setup_routeput(t_routeput **new, t_route *curr)
{
	*new = (t_routeput *)malloc(sizeof(t_routeput));
	if (*new)
	{
		if (copy_roomnames(&(*new)->rooms, curr) == EXIT_SUCCESS)
		{
			if (setup_ants(&(*new)->ants, curr->used) == EXIT_SUCCESS)
			{
				(*new)->rooms_len = curr->used;
				(*new)->ants_received = 0;
				(*new)->finished = 0;
				return (EXIT_SUCCESS);
			}
			free((*new)->rooms);
		}
		free(*new);
	}
	return (EXIT_FAILURE);
}

static ssize_t	setup_all_routeputs(t_routeput ***routes, const t_map *map)
{
	size_t		i;

	*routes = (t_routeput **)malloc(sizeof(t_routeput *) * map->solution.used);
	if (*routes == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < map->solution.used)
	{
		setup_routeput(&(*routes)[i], map->solution.combi[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

static void		delete_routeput(t_routeput **routes, const t_map *map)
{
	size_t	i;

	if (routes == NULL)
		return ;
	i = 0;
	while (i < map->solution.used)
	{
		if (routes[i] != NULL)
		{
			if (routes[i]->rooms != NULL)
			{
				free(routes[i]->rooms);
				routes[i]->rooms = NULL;
			}
			if (routes[i]->ants != NULL)
			{
				free(routes[i]->ants);
				routes[i]->ants = NULL;
			}
			free(routes[i]);
			routes[i] = NULL;
		}
		i++;
	}
}

ssize_t			output_result(const t_input_reader *input, const t_map *map)
{
	t_routeput	**routes;
	size_t		i;
	size_t		curr_ant;

	i = 0;
	curr_ant = 1;
	calculate_ants_per_path(map->antmount, &(map->solution));
	if (setup_all_routeputs(&routes, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	print_input(input);
	while (i < map->solution.turns)
	{
		execute_round(routes, map, &curr_ant);
		i++;
		ft_printf("\n");
	}
	delete_routeput(routes, map);
	free(routes);
	routes = NULL;
	return (EXIT_SUCCESS);
}

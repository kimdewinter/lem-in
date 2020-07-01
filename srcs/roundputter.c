/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   roundputter.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 14:56:15 by kim           #+#    #+#                 */
/*   Updated: 2020/07/01 13:24:52 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void	check_finished(t_routeput *route, size_t antmount_in_route)
{
	if (route->finished == 0 && antmount_in_route == 0)
		route->finished = 1;
}

static void	handle_spacing(const t_routeput *route, const size_t i)
{
		if (route->ants[i + 1] > 0)
			ft_putchar(' ');
}

static void	execute_tail(t_routeput *route, size_t *i)
{
	if (*i > 0)
	{
		if (route->ants[*i - 1] > 0)
		{
			route->ants[*i] = route->ants[*i - 1];
			ft_printf("L%i-%s", route->ants[*i - 1], route->rooms[*i]);
		}
		else
			route->ants[*i] = 0;
		(*i)--;
	}
}

static void	execute_head(t_routeput *route,
							const size_t i,
							const size_t new_ant,
							size_t *antmount_in_route)
{
	if (new_ant > 0)
	{
		handle_spacing(route, i);
		route->ants[0] = new_ant;
		ft_printf("L%i-%s", new_ant, route->rooms[0]);
		(*antmount_in_route)++;
	}
	else
		route->ants[0] = 0;
}

void	execute_route(t_routeput *route, const size_t new_ant)
{
	size_t	i;
	size_t	antmount_in_route;

	i = route->rooms_len - 1;
	antmount_in_route = 0;
	if (new_ant > 0)
		route->ants_received++;
	execute_tail(route, &i);
	while (i > 0)
	{
		if (route->ants[i - 1] > 0)
		{
			handle_spacing(route, i);
			antmount_in_route++;
			route->ants[i] = route->ants[i - 1];
			ft_printf("L%i-%s", route->ants[i - 1], route->rooms[i]);
		}
		else
			route->ants[i] = 0;
		i--;
	}
	execute_head(route, i, new_ant, &antmount_in_route);
	check_finished(route, antmount_in_route);
}

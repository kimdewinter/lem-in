/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   roundputter.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 14:56:15 by kim           #+#    #+#                 */
/*   Updated: 2020/06/10 16:11:20 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void	execute_route(t_routeput *route, const size_t new_ant)
{
	size_t	i;
	size_t	current_antmount_in_route;

	i = route->rooms_len - 1;
	current_antmount_in_route = 0;
	while (i > 0)
	{
		if (route->ants[i - 1] > 0)
		{
			current_antmount_in_route++;
			route->ants[i] = route->ants[i - 1];
			ft_printf("L%i-%s ", route->ants[i - 1], route->rooms[i]);
		}
		else
			route->ants[i] = 0;
		i--;
	}



	if (new_ant > 0)
	{
		current_antmount_in_route++;
		route->ants_received++;
		route->ants[0] = new_ant;
		ft_printf("L%i-%s ", new_ant, route->rooms[0]);
	}
	else
		route->ants[0] = 0;



	if (route->finished == 0 && current_antmount_in_route == 0)
		route->finished = 1;
}

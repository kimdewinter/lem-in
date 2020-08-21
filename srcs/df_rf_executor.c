/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   df_rf_executor.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 15:49:14 by kim           #+#    #+#                 */
/*   Updated: 2020/08/21 16:25:07 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_room			*select_next_room(const t_room *curr, const t_dfs_wrap *wrap)
{
	t_room	*next;
	size_t	i;

	next = NULL;
	i = 0;
	while (i < curr->neighbours_len)
	{
		if (curr->neighbours[i] != NULL)
		{
			if (curr->neighbours[i] == wrap->map->end)
				return (curr->neighbours[i]);
			if ((next == NULL ||
				curr->neighbours[i]->dist_to_end < next->dist_to_end) &&
				room_in_bitfield(curr->neighbours[i], wrap->visited) == 0 &&
				curr->neighbours[i] != wrap->map->start &&
				curr->neighbours[i]->dist_to_end != -1)
			{
				next = curr->neighbours[i];
			}
		}
		i++;
	}
	return (next);
}

static size_t	commit_route(t_dfs_wrap *wrap)
{
	size_t	i;

	if (wrap->candidate->used >= wrap->candidate->len)
		return (handle_err_route_finder(4, NULL));
	i = 0;
	while (i < wrap->route->used)
	{
		bite_add_room_to_bitfield(wrap->route->route[i], wrap->route->bitroute);
		i++;
	}
	wrap->candidate->combi[wrap->candidate->used] = wrap->route;
	wrap->route = NULL;
	wrap->candidate->used++;
	return (EXIT_ROUTEFOUND);
}

ssize_t			exec_find_routes_df(t_room *curr,
									t_dfs_wrap *wrap)
{
	t_room	*next;
	ssize_t	retval;

	if (wrap->route->used >= wrap->route->len)
		return (handle_err_route_finder(3, NULL));
	wrap->route->route[wrap->route->used] = curr;
	wrap->route->used++;
	if (curr == wrap->map->end)
		return (commit_route(wrap));
	bite_add_room_to_bitfield(curr, wrap->visited);
	next = select_next_room(curr, wrap);
	while (next != NULL)
	{
		retval = exec_find_routes_df(next, wrap);
		if (retval == EXIT_FAILURE || retval == EXIT_ROUTEFOUND)
			return (retval);
		next = select_next_room(curr, wrap);
	}
	wrap->route->route[wrap->route->used] = NULL;
	wrap->route->used--;
	return (EXIT_SUCCESS);
}

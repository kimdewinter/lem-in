/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_tubes_utils_3.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 11:46:30 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/20 12:12:25 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		set_conn(t_connection *conn, t_room *nb)
{
	conn->dist = 1;
	conn->dst = nb;
	conn->src_nb = nb;
	if (nb->is_junction == 0)
		find_real_nb(conn);
}

size_t		del_conn(t_room *src, t_room *nb, t_map *map)
{
	size_t ret;

	// printf("DEL CONN\n");
	ret = del_tube(src, nb, map);
	del_tube(nb, src, map);
	return (ret);
}

size_t		remove_path(t_connection *conn, t_map *map)
{
	// printf("REMOVE PATH\n");
	del_conn(conn->dst, conn->dst_nb, map);
	return (del_conn(conn->src, conn->src_nb, map));
}

size_t		handle_loop(t_connection *conn, t_map *map, int *changed)
{
	size_t	ret;

	// printf("\n\nHANDLE LOOP\n\n");
	ret = del_tube(conn->src, conn->src_nb, map);
	del_tube(conn->dst, conn->dst_nb, map);
	del_tube(conn->dst_nb, conn->dst, map);
	del_tube(conn->src_nb, conn->src, map);
	*changed = 1;
	return (ret);
}

int			check_conn(t_connection *conn, size_t *ind, int *changed,
t_map *map)
{
	size_t	res;

	res = 0;
	if (conn->dst == conn->src)
	{
		res = handle_loop(conn, map, changed);
		if (ind != NULL)
			*ind -= res;
		return (0);
	}
	if (conn->dst == NULL)
	{
		res = handle_nowhere_to_go(conn->src, conn->src_nb, map);
		if (ind != NULL)
			*ind -= res;
		return (0);
	}
	return (1);
}

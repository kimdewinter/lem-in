/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_tubes_utils_3.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 11:46:30 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/22 13:27:14 by lravier       ########   odam.nl         */
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
	size_t	ret;
	// printf("REMOVE PATH\n");
	ret = del_conn(conn->src, conn->src_nb, map);
	del_conn(conn->dst, conn->dst_nb, map);
	printf("RET %lu\n", ret);
	return (ret);
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

int			check_conn(t_connection *conn, ssize_t *ind, int *changed,
t_map *map)
{
	ssize_t	res;

	res = 0;
	if (conn->dst == conn->src)
	{
		printf("Handle loop\n");
		res = handle_loop(conn, map, changed);
		if (ind != NULL)
			*ind -= res;
		return (0);
	}
	if (conn->dst == NULL)
	{
		printf("Handle nowhere to go\n");
		*changed = 1;
		res = handle_nowhere_to_go(conn->src, conn->src_nb, map);
		if (ind != NULL)
			*ind -= res;
		return (0);
	}
	if (conn->src == map->start && conn->dist != 1)
	{
		printf("CHECK CONN SPS FOUND\n");
		conn->dst->sps = 1;
		conn->dst->sps_len = conn->dist;
		conn->dst->sps_start = conn->dst_nb;
	}
	if (conn->dst == map->end && conn->dist != 1)
	{
		printf("CHECK CONN SPE FOUND\n");
		conn->src->spe = 1;
		conn->src->spe_len = conn->dist;
		conn->src->spe_start = conn->src_nb;
	}
	return (1);
}

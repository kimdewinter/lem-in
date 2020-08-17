/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_tubes_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 16:29:08 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/17 11:48:19 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

size_t		handle_nowhere_to_go(t_room *src, t_room *nb, t_map *map)
{
	size_t	res;

	res = del_tube(src, nb, map);
	del_tube(nb, src, map);
	return (res);
}

void		setup_conn(t_connection *conn, t_room *src)
{
	conn->add = 1;
	conn->dist = 0;
	conn->dst = src;
	conn->dst_nb = src;
	conn->src = src;
	conn->src_nb = src;
}

int			check_dest(t_connection *conn, t_room *curr)
{
	if (conn->dst == curr || conn->dst_nb == curr)
		return (1);
	return (0);
}

int			check_src(t_connection *conn, t_room *curr)
{
	if (conn->src == curr || conn->src_nb == curr)
		return (1);
	return (0);
}

int			check_dst_src(t_connection *dst, t_connection *src,
t_room *curr)
{
	if (check_dest(dst, curr) == 1 || check_src(src, curr) == 1)
		return (1);
	return (0);
}

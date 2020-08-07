/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unnecessary_tubes_neighbours_checks.c              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 16:55:54 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/04 16:55:54 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		is_nb_of_src(t_connection *side_nb, t_connection *src_side,
t_connection *nb_src, t_map *map)
{
	size_t			i;

	i = 0;
	printf("NB OF SRC CHECK\n");
	while (i < nb_src->src->neighbours_len)
	{
		setup_conn(nb_src, side_nb->dst);
		if (nb_src->src->neighbours[i] != NULL
		&& nb_src->src->neighbours[i] != side_nb->dst
		&& nb_src->src->neighbours[i] != side_nb->dst_nb)
		{
			set_conn(nb_src, nb_src->src->neighbours[i]);
			if (nb_src->dst->is_junction == 0)
				find_real_nb(nb_src->src, nb_src, map);
			if (nb_src->dst == nb_src->src)
			{
				printf("loop\n");
			}
			if (nb_src->dst == NULL)
			{
				printf("nowhere to go\n");
			}
			if (nb_src->dst == src_side->src)
			{
				printf("nb to src\n");
				print_connection(nb_src);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int		is_neighbour_of_other(t_room *dst, t_room *curr, t_map *map)
{
	size_t	i;
	t_connection	tmp;

	i = 0;
	setup_conn(&tmp, curr);
	// printf("IN NB OF OTHER\nDST %s CURR %s\n", dst->name, curr->name);
	while (i < curr->neighbours_len)
	{
		setup_conn(&tmp, curr);
		if (curr->neighbours[i] != NULL)
		{
			set_conn(&tmp, curr->neighbours[i]);
			if (tmp.dst->is_junction == 0)
				find_real_nb(tmp.src, &tmp, map);
			// if (tmp.dst)
			// 	printf("DST FOUND %s\n", tmp.dst->name);
			if (tmp.dst == NULL)
				printf("nowehere to go\n");
			if (tmp.dst == dst)
				return (1);
		}
		i++;
	}
	// printf("Not nb of other\n");
	return (0);
}
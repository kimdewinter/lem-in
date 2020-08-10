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
	if (room_in_bitfield(src_side->src, nb_src->src->removed_conns) == 1)
	{
		if (DEBUG == 1)
			printf("Connection to %s was already removed from %s\n", src_side->src->name, 
			nb_src->src->name);
		return (1);
	}
	if (DEBUG == 1)
		printf("NB %s\n", nb_src->src->name);
	while (i < nb_src->src->neighbours_len)
	{
		setup_conn(nb_src, side_nb->dst);
		if (nb_src->src->neighbours[i] != NULL
		&& nb_src->src->neighbours[i] != side_nb->dst
		&& nb_src->src->neighbours[i] != side_nb->dst_nb)
		{
			if (DEBUG == 1)
			{
				printf("Candidate %s %d\n", nb_src->src->neighbours[i]->name, nb_src->src->neighbours[i]->is_junction);
				for (size_t j = 0; j < nb_src->src->neighbours[i]->neighbours_len; j++)
				printf("nb %s ", nb_src->src->neighbours[i]->neighbours[j]->name);
				printf("\n\n");
			}
			set_conn(nb_src, nb_src->src->neighbours[i]);
			if (nb_src->dst->is_junction == 0)
				find_real_nb(nb_src, map);
			if (nb_src->dst == nb_src->src)
			{
				if (DEBUG == 1)
					printf("loop\n");
			}
			if (nb_src->dst == NULL)
			{
				if (DEBUG == 1)
					printf("nowhere to go\n");
			}
			if (nb_src->dst == src_side->src)
			{
				if (DEBUG == 1)
				{
					printf("nb to src\n");
					print_connection(nb_src);
				}
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int		is_nb_of_other(t_room *dst, t_room *curr, t_map *map)
{
	size_t	i;
	t_connection	tmp;

	i = 0;
	setup_conn(&tmp, curr);
	if (room_in_bitfield(dst, curr->removed_conns) == 1)
	{
		if (DEBUG == 1)
			printf("Connection to %s was already remove from %s\n", dst->name, 
		curr->name);
		return (1);
	}
	if (DEBUG == 1)
		printf("IN NB OF OTHER\nDST %s CURR %s\n", dst->name, curr->name);
	while (i < curr->neighbours_len)
	{
		setup_conn(&tmp, curr);
		if (curr->neighbours[i] != NULL)
		{
			set_conn(&tmp, curr->neighbours[i]);
			if (tmp.dst->is_junction == 0)
				find_real_nb(&tmp, map);
			if (tmp.dst == NULL)
			{
				if (DEBUG == 1)
					printf("nowehere to go\n");
			}
			if (tmp.dst == dst)
				return (1);
		}
		i++;
	}
	// printf("Not nb of other\n");
	return (0);
}
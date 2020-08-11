/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unnecessary_tubes_options_check.c                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 16:54:17 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/04 16:54:17 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		alt_opts_side(t_connection *side_nb, t_connection *src_side, t_map *map,
int *changed)
{
	size_t			i;
	t_connection	side_dst;

	i = 0;
	(void)map;
	if (DEBUG == 1)
		printf("Alt options\n");
	setup_conn(&side_dst, src_side->dst);
	// len = side_dst.src->neighbours_len;
	while (i < side_dst.src->neighbours_len)
	{
		setup_conn(&side_dst, src_side->dst);
		if (check_dst_src(src_side, &side_dst,
		side_dst.src->neighbours[i]) == 0)
		{
			set_conn(&side_dst, side_dst.src->neighbours[i]);
			if (side_dst.dst->is_junction == 0)
				find_real_nb(&side_dst, map);
			/* CHECK THIS */
			if (side_dst.dst == NULL)
			{
				if (DEBUG == 1)
					printf("Nowhere to go alt opts side\n");
				i -= handle_nowhere_to_go(side_dst.src, side_dst.src_nb, map);
				*changed = 1;
				// exit (0);
			}
			if (side_dst.dst == side_dst.src)
			{
				if (DEBUG == 1)
					printf("Loop\n");
				handle_loop(&side_dst, map, changed, &i);
			}
			if (DEBUG == 1)
			{
				printf("BEFORE IS NB OF OTHER CHECK\n");
				printf("%s\n", side_dst.dst->name);
			}
			if (side_dst.dst != side_nb->dst
				&& side_dst.dst != src_side->src
				&& is_nb_of_other(side_dst.dst, side_nb->dst, map, changed) == 0)
					return (1);
		}
		i++;
	}
	return (0);
}

int		alt_opts_nb(t_connection *side_nb, t_connection *src_side,
t_connection *nb_src, t_map *map, int *changed)
{
	size_t			i;
	t_connection	nb_dst;

	i = 0;
	(void)map;

	setup_conn(&nb_dst, nb_src->src);
	while (i < nb_dst.src->neighbours_len)
	{
		setup_conn(&nb_dst, nb_src->src);
		if (check_dst_src(src_side, side_nb, nb_dst.src->neighbours[i])
		== 0)
		{
			set_conn(&nb_dst, nb_dst.src->neighbours[i]);
			if (nb_dst.dst->is_junction == 0)
				find_real_nb(&nb_dst, map);
			/* CHECK THIS NB CAN ALREADY GO TO SRC*/
			if (nb_dst.dst == NULL)
			{
				i -= handle_nowhere_to_go(nb_dst.src, nb_dst.src_nb, map);
				*changed = 1;
				if (DEBUG == 1)
					printf("Nowhere to go alt opt nbs\n");
					// exit (0);
			}
			if (nb_dst.dst == nb_dst.src)
			{
				if (DEBUG == 1)
					printf("Loop\n");
				handle_loop(&nb_dst, map, changed, &i);
			}
			if (DEBUG == 1)
			{
				printf("Side nb\n");
				print_connection(side_nb);
				printf("nb dst\n");
				print_connection(&nb_dst);
			}
			if (nb_dst.dst != side_nb->src
				&& nb_dst.dst != nb_src->dst
				&& is_nb_of_other(nb_dst.dst, side_nb->src, map, changed) == 0)
					return (1);
		}
		i++;
	}
	return (0);
}
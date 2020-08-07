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

int		alt_opts_side(t_connection *side_nb, t_connection *src_side)
{
	size_t			i;
	size_t			len;
	t_connection	side_dst;

	i = 0;
	setup_conn(&side_dst, src_side->dst);
	len = side_dst.src->neighbours_len;
	while (i < len)
	{
		setup_conn(&side_dst, src_side->dst);
		if (side_dst.src->neighbours[i] != NULL
		&& check_dst_src(src_side, &side_dst,
		side_dst.src->neighbours[i]) == 0)
		{
			set_conn(&side_dst, side_dst.src->neighbours[i]);
			if (side_dst.dst->is_junction == 0)
				find_real_nb(&side_dst);
			/* CHECK THIS */
			if (side_dst.dst == NULL)
				printf("Nowhere to go\n");
			if (side_dst.dst == side_dst.src)
				printf("Loop\n");
			/**/
			if (side_dst.dst != side_nb->dst
				&& side_dst.dst != src_side->src
				&& is_neighbour_of_other(side_dst.dst, side_nb->dst) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int		alt_opts_nb(t_connection *side_nb, t_connection *src_side,
t_connection *nb_src)
{
	size_t			i;
	size_t			len;
	t_connection	nb_dst;

	i = 0;
	setup_conn(&nb_dst, nb_src->src);
	len = nb_dst.src->neighbours_len;
	while (i < len)
	{
		setup_conn(&nb_dst, nb_src->src);
		if (nb_dst.src->neighbours[i] != NULL
		&& check_dst_src(src_side, side_nb, nb_dst.src->neighbours[i])
		== 0)
		{
			set_conn(&nb_dst, nb_dst.src->neighbours[i]);
			if (nb_dst.dst->is_junction == 0)
				find_real_nb(&nb_dst);
			/* CHECK THIS NB CAN ALREADY GO TO SRC*/
			if (nb_dst.dst == NULL)
				printf("Nowhere to go\n");
			if (nb_dst.dst == nb_dst.src)
				printf("Loop\n");
			/**/
			if (nb_dst.dst != side_nb->src
				&& nb_dst.dst != nb_src->dst 
				&& is_neighbour_of_other(nb_dst.dst, side_nb->src) == 0)
					return (1);
		}
		i++;
	}
	return (0);
}
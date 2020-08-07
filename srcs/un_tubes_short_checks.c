/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unnecessary_tubes_checks.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 16:51:22 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/04 16:51:22 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t	check_adv_nb(t_connection *src_side, t_connection *side_nb,
t_connection *nb_dst, t_map *map)
{
	size_t			j;
	t_connection 	side_dst;
	size_t			nb_dst_adv;

	j = 0;
	nb_dst_adv = 0;
	setup_conn(&side_dst, src_side->dst);
	while (j < side_dst.src->neighbours_len)
	{
		setup_conn(&side_dst, src_side->dst);
		if (side_dst.src->neighbours[j] != NULL
		&& check_dst_src(src_side, side_nb, side_dst.src->neighbours[j]) == 0)
		{
			set_conn(&side_dst, side_dst.src->neighbours[j]);
			if (side_dst.dst->is_junction == 0)
				find_real_nb(side_dst.src,
				&side_dst, map);
			if (side_dst.dst == nb_dst->dst)
			{
				if ((nb_dst->dist + side_nb->dist) < side_dst.dist)
					nb_dst_adv++;
			}
		}
		j++;
	}
	return (nb_dst_adv);
}

int				shrt_conn_dsts_nb(t_connection *src_side,
t_connection *nb_src, t_connection *side_nb, t_map *map)
{
	int				nb_dst_adv;
	t_connection	nb_dst;
	size_t			i;

	setup_conn(&nb_dst, side_nb->dst);
	nb_dst_adv = 0;
	i = 0;
	while (i < nb_dst.src->neighbours_len)
	{
		setup_conn(&nb_dst, side_nb->dst);
		if (nb_dst.src->neighbours[i] != NULL
		&& check_dst_src(side_nb, nb_src, nb_dst.src->neighbours[i]) == 0)
		{
			set_conn(&nb_dst, nb_dst.src->neighbours[i]);
			if (nb_dst.dst->is_junction == 0)
				find_real_nb(nb_dst.src, &nb_dst, map);
			nb_dst_adv += check_adv_nb(src_side, side_nb, &nb_dst, map);
		}
		i++;
	}
	return (nb_dst_adv);
}

static size_t	check_adv_side(t_connection *src_side, t_connection *side_nb,
t_connection *nb_dst, t_map *map)
{
	size_t			side_dst_adv;
	size_t			j;
	t_connection	side_dst;

	j = 0;
	side_dst_adv = 0;
	setup_conn(&side_dst, src_side->dst);
	while (j < side_dst.src->neighbours_len)
	{
		setup_conn(&side_dst, src_side->dst);
		if (side_dst.src->neighbours[j] != NULL
		&& check_dst_src(src_side, side_nb, side_dst.src->neighbours[j])
		== 0)
		{
			set_conn(&side_dst, side_dst.src->neighbours[j]);
			if (side_dst.dst->is_junction == 0)
				find_real_nb(side_dst.src,
				&side_dst, map);
			if (side_dst.dst == nb_dst->dst)
			{
				// print_connection(&side_dst);
				// print_connection(nb_dst);
				// print_connection(side_nb);
				// printf("Side dst + side nb %lu nb dst %lu\n", (side_dst.dist + side_nb->dist), nb_dst->dist);
				if ((side_dst.dist + side_nb->dist) < nb_dst->dist)
				{
					side_dst_adv++;
				}
			}
		}
		j++;
	}
	return (side_dst_adv);	
}

/* Check whether going through side from nb is advantageous */

int				shrt_conn_dsts_side(t_connection *src_side,
t_connection *nb_src, t_connection *side_nb, t_map *map)
{
	int				side_dst_adv;
	t_connection	nb_dst;
	size_t			i;

	setup_conn(&nb_dst, side_nb->dst);
	side_dst_adv = 0;
	i = 0;
	while (i < nb_dst.src->neighbours_len)
	{
		setup_conn(&nb_dst, side_nb->dst);
		if (nb_dst.src->neighbours[i] != NULL
		&& check_dst_src(side_nb, nb_src, nb_dst.src->neighbours[i]) == 0)
		{
			set_conn(&nb_dst, nb_dst.src->neighbours[i]);
			if (nb_dst.dst->is_junction == 0)
				find_real_nb(nb_dst.src, &nb_dst, map);
			side_dst_adv += check_adv_side(src_side, side_nb, &nb_dst, map);
		}
		i++;
	}
	printf("Advantage when taking side from nb %d\n", side_dst_adv);
	return (side_dst_adv);
}
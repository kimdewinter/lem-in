/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_tubes_short_checks.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 16:30:32 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/13 19:29:23 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static size_t	check_adv_nb(t_connection *src_side, t_connection *side_nb,
t_connection *nb_dst)
{
	size_t			j;
	t_connection	side_dst;
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
t_connection *nb_src, t_connection *side_nb)
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
			nb_dst_adv += check_adv_nb(src_side, side_nb, &nb_dst);
		}
		i++;
	}
	return (nb_dst_adv);
}

static size_t	check_adv_side(t_connection *src_side, t_connection *side_nb,
t_connection *nb_dst)
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
			if (side_dst.dst == nb_dst->dst)
			{
				if ((side_dst.dist + side_nb->dist) < nb_dst->dist)
					side_dst_adv++;
			}
		}
		j++;
	}
	return (side_dst_adv);
}

int				shrt_conn_dsts_side(t_connection *src_side,
t_connection *nb_src, t_connection *side_nb)
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
			side_dst_adv += check_adv_side(src_side, side_nb, &nb_dst);
		}
		i++;
	}
	return (side_dst_adv);
}

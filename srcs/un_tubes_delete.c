/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_tubes_delete.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 14:42:03 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/22 16:03:12 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int			remove_dupl_path(t_connection *side_nb, t_connection *q,
t_map *map, int *changed)
{
	// printf("Remove dupl path\n");
	// print_connection(q);
	// print_connection(side_nb);
	if (side_nb->dist < q->dist)
	{
		*changed = 1;
		remove_path(q, map);
		return (0);
	}
	else
	{
		*changed = 1;
		remove_path(side_nb, map);
		return (1);
	}
}

static int			update_src_path(t_connection *q, t_map *map, int *changed,
ssize_t *i)
{
	printf("\n\nUPDATE SRC PATH\n\n");
	if (q->dst->is_junction == 0)
	{
		// printf("Start %s nb %s\n", q->dst->name, q->dst_nb->name);
		find_real_nb(q);
		if (check_conn(q, i, changed, map) == 0)
		{
			// printf("UPDATE SRC PATH DONE\n");
			return (0);
		}
	}
	print_connection(q);
	printf("UPDATE SRC PATH DONE\n");
	return (1);
}

static int			is_duplicate_path(t_triangle *tr, t_map *map)
{
	if (tr->side_nb.dst == tr->src_side->src
	&& tr->side_nb.src == tr->src_side->dst
	&& !(tr->src_side->src == map->start
	&& tr->src_side->dst == map->end))
		return (1);
	return (0);
}

static int			handle_conn_removal(ssize_t *i, t_triangle *tr, int *changed,
t_map *map)
{
	ssize_t	prev_i;
	t_room	*prev;

	prev_i = 0;
	prev = NULL;
	printf("\n\nHANDLE CONN REMOVAL\n\n");
	if (check_conn(&tr->side_nb, i, changed, map) == 1)
	{
		if (is_duplicate_path(tr, map) == 1)
		{
			printf("\n\nIS DUPL PATH\n\n");
			prev_i = *i;
			*i -= remove_dupl_path(&tr->side_nb, tr->src_side, map, changed);
			if (prev_i == *i)
				return (1);
		}
		else if (is_nb_of_src(tr, map, changed) == 1)
		{
			printf("\n\nREMOVE IF UN\n\n");
			// print_triangle(tr);
			// exit (0);
			prev = tr->src_side->dst->neighbours[*i];
			remove_if_un(tr, map, changed);
			if (tr->src_side->dst->neighbours[*i] != prev)
				(*i)--;
		}
	}
	// printf("\n\nAFTER HANDLE CONN REMOVAL\n\n");
	return (0);
}

static int			is_legal_path_sps(t_connection *side_nb,
int *changed, ssize_t *i, t_map *map)
{
	/* Can side go through nb */
	/* i -= if we remove a nb from side src */
	// print_connection(side_nb);
	if (side_nb->dst->sps == 1 && side_nb->src->sps == 1
	&& (side_nb->dst != map->end && side_nb->src != map->end))
	{
		printf("side has sps len %lu and nb has sps len %lu\n", side_nb->src->sps_len, side_nb->dst->sps_len);
		if ((side_nb->src->sps_len + side_nb->dist) >= side_nb->dst->sps_len)
		{
			printf("side sps len + dist >= nb sps len\nNOT LEGAL\n");
			// if (side_nb->src == map->end || side_nb->dst == map->end)
			// {
			// 	printf("PRINT MAP\n\n");
			// 	print_map(map);
			// 	exit (0);
			// }
			if ((side_nb->dst->sps_len + side_nb->dist) >= side_nb->src->sps_len)
			{
				*changed = 1;
				printf("nb to side also illegal\nREMOVE WHOLE PATH %ld\n", *i);
				print_connection(side_nb);
				(*i) -= remove_path(side_nb, map);
				printf("%ld\n", *i);
			}
			else
			{
				printf("REMOVE JUST from side to nb\n");
				set_unavailable(side_nb->src, side_nb->src_nb, changed, map);
				if (side_nb->dist != 1)
					set_unavailable(side_nb->dst_nb, side_nb->dst, changed, map);
			}
			return (0);
			// exit (0);
		}
		else
			return (1);
	}
	return (1);
}

static int			is_legal_path_spe(t_connection *side_nb,
int *changed, ssize_t *i, t_map *map)
{
	/* Can side go through nb */
	/* i -= if we remove a nb from side src */
	// (void)i;
	// (void)changed;
	printf("Is legal path check spe\n");
	// print_connection(side_nb);
	if (side_nb->dst->spe == 1 && side_nb->src->spe == 1
	&& (side_nb->dst != map->start && side_nb->src != map->start))
	{
		printf("side has sps len %lu and nb has sps len %lu\n", side_nb->src->spe_len, side_nb->dst->spe_len);
		if ((side_nb->src->spe_len + side_nb->dist) >= side_nb->dst->spe_len)
		{
			printf("side sps len + dist >= nb sps len\nNOT LEGAL\n");
			if ((side_nb->dst->spe_len + side_nb->dist) >= side_nb->src->spe_len)
			{
							*changed = 1;

				printf("nb to side also illegal\nREMOVE WHOLE PATH %ld\n", *i);
				*i -= remove_path(side_nb, map);
				printf("%ld\n", *i);
			}
			else
			{
				printf("REMOVE JUST from side to nb\n");
				set_unavailable(side_nb->dst, side_nb->dst_nb, changed, map);
				if (side_nb->dist != 1)
					set_unavailable(side_nb->src_nb, side_nb->src, changed, map);
			}
			return (0);
			// exit (0);
		}
		else
			return (1);
	}
	return (1);
}

int					del_un_tubes(t_connection *q, int *changed, t_map *map)
{
	ssize_t			i;
	t_triangle		curr;

	i = 0;
	curr.src_side = q;
	printf("\n\nDEL UN TUBES\n\n");
	setup_conn(&curr.side_nb, q->dst);
	while ((size_t)i < q->dst->neighbours_len)
	{
		printf("nb len %lu\n", q->dst->neighbours_len);
		setup_conn(&curr.side_nb, q->dst);
		if (q->dst->neighbours[i] != q->dst_nb
		&& room_in_bitfield(q->dst->neighbours[i], q->dst->unavailable) == 0)
		{
			set_conn(&curr.side_nb, q->dst->neighbours[i]);
			// printf("check conn %d\n", check_conn(&curr.side_nb, &i, changed, map));
			printf("i: %ld\n", i);
			// print_connection(&curr.side_nb);
			if (check_conn(&curr.side_nb, &i, changed, map) == 1)
			{
				printf("CHECK CONN IS OKAY\n");
					print_connection(q);
					print_connection(&curr.side_nb);
				if (is_legal_path_sps(&curr.side_nb, changed, &i, map) == 1
				&& is_legal_path_spe(&curr.side_nb, changed, &i, map) == 1)
				{
					if (handle_conn_removal(&i, &curr, changed, map) == 1)
						return (1);
				}
				if (update_src_path(q, map, changed, &i) == 0)
				{
					return (1);
				}
								printf("After update src path\n");
					print_connection(q);
				printf("after i: %ld\n", i);
			}
		}
		i++;
	}
	// printf("AFTER DEL UN TUBES\n");
	return (1);
}

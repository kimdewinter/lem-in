/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   del_un_tubes.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 16:25:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/04 16:25:25 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int		remove_if_un(t_connection *src_side,
t_connection *nb_src, t_connection *side_nb, t_map *map)
{
	int		add_opt_nb_side;
	int		add_opt_side_nb;
	int		changed;

	changed = 0;
	// printf("\n\nREMOVE IF UN\n");
	// printf("SRC %s SIDE %s NB %s\n", src_side->src->name, src_side->dst->name,
	// side_nb->dst->name);
	add_opt_nb_side = alt_opts_nb(side_nb, src_side, nb_src, map);
	add_opt_side_nb = alt_opts_side(side_nb, src_side, nb_src, map);
	if (add_opt_nb_side == 0 && add_opt_side_nb == 0)
	{
		printf("Neither adds option to other\n");
		changed = rm_un_conn(side_nb, src_side, nb_src, map);
		printf("\n\nchanged after rm un conn %d\n\n", changed);
	}
	else if (add_opt_nb_side == 0)
	{
		printf("nb doesnt add option to side\n");
		if (shrt_conn_dsts_nb(src_side, nb_src, side_nb, map) == 0
		&& has_conn_to(side_nb->src, side_nb->src_nb) == 1)
		{
			changed = 1;
			del_tube(side_nb->src, side_nb->src_nb, map);
		}
	}
	else if (add_opt_side_nb == 0)
	{
		// printf("side doesnt add option to nb side %s\n", side_nb->src->name);
		if (shrt_conn_dsts_side(src_side, nb_src, side_nb, map) == 0
		&& has_conn_to(side_nb->dst, side_nb->dst_nb) == 1)
		{
			printf("Not better to go through side\n");
			changed = 1;
			del_tube(side_nb->dst, side_nb->dst_nb, map);
		}
		// exit (0);
	}
	return (changed);
}

static void		remove_dupl_path(t_connection *side_nb, t_connection *q, t_map *map,
int *changed)
{
	if (side_nb->dist < q->dist)
	{
		*changed = 1;
		del_tube(q->dst, q->dst_nb, map);
		del_tube(q->src, q->src_nb, map);
	}
	else
	{
		*changed = 1;
		del_tube(side_nb->dst, side_nb->dst_nb, map);
		del_tube(side_nb->src, side_nb->src_nb, map);
	}
}

static int	update_src_path(t_connection *q, t_map *map, int *changed,
size_t *i)
{
	printf("UPDATE\n");
	if (q->dst->is_junction == 0)
	{
		find_real_nb(q->dst, q, map);
		printf("after find real nb\n");
		*i = -1;
		if (q->dst == NULL)
		{
			printf("NOWHERE TO GO dst nb %s src nb %s\n", q->src_nb->name, q->dst_nb->name);
			del_tube(q->src_nb, q->dst_nb, map);
			del_tube(q->dst_nb, q->src_nb, map);
			return (0);
		}
		if (q->src == q->dst)
		{
			*changed = 1;
			del_tube(q->dst, q->dst_nb, map);
			del_tube(q->src, q->src_nb, map);
			return (0);
		}
	}
	return (1);
}

void	handle_loop(t_connection *conn, t_map *map, int *changed, size_t *i)
{
	del_tube(conn->dst, conn->dst_nb, map);
	del_tube(conn->src, conn->src_nb, map);
	*changed = 1;
	*i = -1;
}

int			del_un_tubes(t_conn_wrap *qr, t_connection *q, int *changed, t_map *map)
{
	size_t			i;
	int				res;
	t_room			*prev;
	t_connection 	side_nb;
	t_connection	nb_src;

	i = 0;
	res = 0;
	prev = NULL;
	printf("DEL TUBE\n");
	setup_conn(&side_nb, q->dst);
	while (i < q->dst->neighbours_len)
	{
		setup_conn(&side_nb, q->dst);
		if (q->dst->neighbours[i] != NULL && q->dst->neighbours[i] != q->dst_nb)
		{
			set_conn(&side_nb, q->dst->neighbours[i]);
			if (q->dst->neighbours[i]->is_junction == 0)
				find_real_nb(q->dst, &side_nb, map);
			if (side_nb.dst == NULL)
			{
				printf("nowhere to go\n");
			}
			if (side_nb.dst == side_nb.src)
			{
				/* Is loop from dst so doesnt affect iter */
				handle_loop(&side_nb, map, changed, &i);
			}
			else if (side_nb.dst == q->src && side_nb.src == q->dst
			&& !(q->src == map->start && q->dst == map->end))
			{
				printf("REMOVE DUPLICATE PATH\n");
				remove_dupl_path(&side_nb, q, map, changed);
				i--;
				printf("i: %lu\n", i);
			}
			else
			{
				printf("REGULAR ROUTE\n");
				printf("Conn src to side\n");
				print_connection(q);
				printf("Conn side to nb\n");
				print_connection(&side_nb);
				setup_conn(&nb_src, side_nb.dst);
				if (is_nb_of_src(&side_nb, q, &nb_src, map) == 1)
				{
					printf("NB OF SRC\n");
					prev = q->dst->neighbours[i];
					res = remove_if_un(q, &nb_src, &side_nb, map);
					if (q->dst->neighbours[i] != prev)
						i--;
					if (*changed == 0)
						*changed = res;
				}
				printf("NOT NB OF SRC\n");
			}
			if (update_src_path(q, map, changed, &i) == 0)
				return (0);
		}
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 16:00:39 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/01 16:00:39 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	print_map(t_map *map)
{
	t_table *table;
	t_room *tmp;

	table = map->rooms;
	ft_printf("\nPRINT MAP\n\n");
	if (map->start)
		ft_printf("START: %s\n", map->start->name);
	if (map->end)
		ft_printf("END: %s\n", map->end->name);
	for (size_t i = 0; i < table->size; i++)
	{
		if (table->entries[i] != NULL)
		{
			ft_printf("KEY: %s\nSPE %d\nSPS %d\nWEIGHT %lu\nJUNCTION %d\n", table->entries[i]->key
			, ((t_room *)table->entries[i]->val)->spe,
			((t_room *)table->entries[i]->val)->sps,
			((t_room *)table->entries[i]->val)->weight,
			((t_room *)table->entries[i]->val)->is_junction);
			tmp = (t_room *)table->entries[i]->val;
			// printf("ID: %lu\nDead end: %d\n", tmp->room_i, tmp->dead_end);
			for (size_t j = 0; j < tmp->neighbours_len; j++)
				ft_printf("NEIGHBOUR: ID %d KEY %s\n", j, tmp->neighbours[j]->name);
			printf("\n\n");
		}
	}
}

void		print_connection_queue(t_connection **q)
{
	t_connection *iter;

	iter = *q;
	printf("QUEUE\n");
	while (iter)
	{
		printf("\n\nSRC %s\nSRC NB: %s\nDST %s\nDST NB: %s\nDISTANCE %lu\n\n\n",
		iter->src->name, iter->src_nb->name,
		iter->dst->name, iter->dst_nb->name, iter->dist);
		iter = iter->next;
	}
}

void		print_connection(t_connection *tmp)
{
	printf("\nCONNECTION\n");
	printf("\n\nSRC: %s %d\nSRC NB: %s %d\nDST: %s %d\nDST NB: %s %d\nDIST %lu\n\n\n",
	tmp->src->name, tmp->src->is_junction ,tmp->src_nb->name, 
	tmp->src_nb->is_junction ,tmp->dst->name, 
	tmp->dst->is_junction, tmp->dst_nb->name,tmp->dst_nb->is_junction, tmp->dist);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_unnecessary_tubes_2.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/04 16:34:41 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/04 16:34:41 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_connection		*new_connection(t_connection *item)
{
	t_connection	*new;

	new = (t_connection *)malloc(sizeof(t_connection));
	if (new)
	{
		new->add = 1;
		new->src = item->src;
		new->src_nb = item->src_nb;
		new->dst = item->dst;
		new->dst_nb = item->dst_nb;
		new->dist = item->dist;
		new->prev = NULL;
		new->next = NULL;
		return (new);
	}
	return (NULL);
}

int		is_junction(t_room *curr, t_map *map)
{
	/* ONE real way to go and ONE real way to get there */
	if (curr == map->start || curr == map->end)
		return (1);
	if (curr->neighbours_len == 1 && curr->conns_to == 1)
		return (0);
	// if (curr->spe == 1)
	// 	return (0);
	// if (curr->sps == 1)
	// 	return (0);
	if (curr->neighbours_len == 2)
	{
		if (curr->conns_to == 1)
		{
			if (is_mutual_conn(curr, curr->neighbours[0]) == 1
			|| is_mutual_conn(curr, curr->neighbours[1]) == 1)
				return (0);
		}
		if (curr->conns_to == 2)
		{
			if (is_mutual_conn(curr, curr->neighbours[0]) == 1
			&& is_mutual_conn(curr, curr->neighbours[1]) == 1)
				return (0);
		}
	}
	return (1);
}

int				del_tube(t_room *from, t_room *to, t_map *map)
{
	int		found;
	int		ret;
	size_t	i;
	t_room 	*tmp;

	i = 0;
	found = 0;
	ret = 0;
	// printf("From %s %lu to %s\n", from->name, from->neighbours_len, to->name);
	// if (strcmp(from->name, "2") == 0
	// && strcmp(to->name, "3") == 0)
	// 	exit (0);
	while (i < from->neighbours_len && found == 0)
	{
		if (from->neighbours[i] == to)
		{
			add_to_bitfield(to, from->removed_conns);
			if (DEBUG == 1)
				printf("Remove connection to %s from %s\n", from->neighbours[i]->name, from->name);
			if (from->neighbours_len == 1)
			{
				from->neighbours[i] = NULL;
				ret = 0;
			}
			else
			{
				tmp = from->neighbours[from->neighbours_len - 1];
				from->neighbours[from->neighbours_len - 1] = NULL;
				from->neighbours[i] = tmp;
				ret = 1;
			}
			found = 1;
		}
		i++;
	}
	// printf("Found %d\n",found);
	if (found == 1)
	{
		// printf("conns to %lu\nto nb len %lu\njunction %d\n", to->conns_to,
		// to->neighbours_len, to->is_junction);
		to->conns_to--;
		from->neighbours_len--;
		if (is_junction(to, map) == 0)
			to->is_junction = 0;
		if (is_junction(from, map) == 0)
			from->is_junction = 0;
		if (DEBUG == 1)
		{
			printf("To %s is junction %d\n", to->name, to->is_junction);
			printf("From %s is junction %d\n", from->name, from->is_junction);
		}
		// for (size_t i = 0; i < to->neighbours_len; i++)
		// 	printf("%s ", to->neighbours[i]->name);
		// if (from->neighbours_len == 2 && (from != map->start && from != map->end))
		// 	from->is_junction = 0;
	}
	if (DEBUG == 1)
		printf("After del\n");
	return (ret);
}

static void		find_next(t_connection *tmp, t_room **curr, t_room **nb,
t_map *map, int *found)
{
	(void)map;
	// && !((*curr)->sps == 1 && *nb != map->start)
	// && !((*curr)->spe == 1 && *nb != map->end)
	if (*nb != tmp->dst_nb
	&& *nb != tmp->dst)
	{
		if ((*nb)->is_junction == 0)
		{
			if (DEBUG == 1)	
				printf("Found %s\n", (*nb)->name);
			*found = 1;
			tmp->dist++;
		}
		if (DEBUG == 1)
			printf("Found %s %d\n", (*nb)->name, (*nb)->is_junction);
		tmp->dst_nb = *curr;
		*curr = *nb;
	}
}

void		find_real_nb(t_connection *tmp, t_map *map)
{
	size_t	i;
	t_room	*nb;
	int		found;

	i = 0;
	nb = tmp->dst;
	found = 1;
	tmp->dist++;
	while (nb->is_junction == 0 && found == 1)
	{
		found = 0;
		i = 0;
		while (i < nb->neighbours_len)
		{
			if (nb->neighbours[i] != NULL)
			{
				find_next(tmp, &nb, &(nb->neighbours[i]), map, &found);
				if (DEBUG == 1)
					printf("found %d\n", found);
				if ((found == 0 && nb->is_junction == 1) || found == 1)
					break;
			}
			i++;
		}
		if (found == 0 && nb->is_junction == 0)
		{
			tmp->dst = NULL;
			return ;
		}
	}
	if (nb)
	{
		if (DEBUG == 1)
			printf("Last found %s\n", nb->name);
	}
	if (DEBUG == 1)
		printf("Done\n");
	tmp->dst = nb;
}
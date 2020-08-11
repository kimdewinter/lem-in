/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sanitize_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 16:41:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/11 16:39:06 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		is_mutual_conn(t_room *curr, t_room *nb)
{
	size_t	i;

	i = 0;
	while (i < nb->neighbours_len)
	{
		if (nb->neighbours[i] == curr)
			return (1);
		i++;
	}
	return (0);
}

static int		is_dead_end_first(t_room *curr)
{
	/* Can't go anywhere or we can't end up here*/
	if (curr->neighbours_len == 0 || curr->conns_to == 0)
		return (1);
	if (curr->neighbours_len == 1)
	{
		/* Can only go back to where it came from */
		if (curr->conns_to == 1 && is_mutual_conn(curr, curr->neighbours[0])
		== 1)
			return (1);
	}
	return (0);
}

static int		is_dead_end_cont(t_room *curr)
{
	if (curr->neighbours_len > 2)
		return (0);
	if (curr->neighbours_len == 1)
	{
		if (curr->conns_to == 1)
			return (1);
		if (curr->conns_to == 2)
		{
			if (is_mutual_conn(curr, curr->neighbours[0]) == 1)
				return (1);
		}
	}
	if (curr->neighbours_len == 2)
	{
		if (curr->conns_to == 1)
			return (1);
		if (curr->conns_to == 2)
		{
			if (DEBUG == 1)
			{
				printf("curr %s\n", curr->name);
				for (size_t i = 0; i < curr->neighbours_len; i++)
					printf("%s ", curr->neighbours[i]->name);
				printf("\n\n");
			}
			if (is_mutual_conn(curr, curr->neighbours[0]) == 1
			|| is_mutual_conn(curr, curr->neighbours[1]) == 1)
				return (1);
		}
	}
	return (0);
}

static void		remove_dead_end_from_nbs(t_room *dead, t_map *map)
{
	size_t	i;
	size_t	j;
	t_room	*nb;
	// t_room	*tmp;

	i = 0;
	(void)map;
	if (DEBUG == 1)
		printf("Remove dead ends from nbs dead %s\n", dead->name);
	while (i < dead->neighbours_len)
	{
		if (dead->neighbours[i] != NULL)
		{
			j = 0;
			nb = dead->neighbours[i];
			if (DEBUG == 1)
				printf("Nb %s\n", nb->name);
			while (j < nb->neighbours_len)
			{
				if (DEBUG == 1)
					printf("nbs nb %s\n", nb->neighbours[j]->name);
				if (nb->neighbours[j] == dead)
				{
					if (DEBUG == 1)
						printf("Is dead\n");
					j -= handle_nowhere_to_go(nb, dead, map);
					// if (has_conn_to(nb->neighbours[j], dead) == 1)
					// {
					// 	printf("Has conn to dead\n");
					// 	del_tube(nb->neighbours[j], dead, map);
					// }
					// if (nb->neighbours_len == 1)
					// 	nb->neighbours[j] = NULL;
					// else
					// {
					// 	tmp = nb->neighbours[nb->neighbours_len - 1];
					// 	nb->neighbours[nb->neighbours_len - 1] = NULL;
					// 	nb->neighbours[j] = tmp;
					// }
					// nb->neighbours_len--;
					// j--;
					break;
				}
				j++;
			}
		}
		i++;
	}
}

static void		remove_dead_path(t_room **tmp, t_map *map)
{
	t_room	*prev;
	size_t	j;

	prev = *tmp;
	if (*tmp == NULL
	|| (*tmp)->neighbours == NULL
	|| (*tmp)->neighbours_len == 0)
		return ;
	*tmp = *((*tmp)->neighbours);
	j = 0;
	if (DEBUG == 1)
		printf("Remove dead path\n");
	while (*tmp != NULL
	&& is_dead_end_cont(*tmp) == 1
	&& *tmp != map->start
	&& *tmp != map->end)
	{
		if (DEBUG == 1)
		{
			printf("Curr: %s\n", (*tmp)->name);
			for (size_t j = 0; j < (*tmp)->neighbours_len; j++)
					printf("nbs %s ", (*tmp)->neighbours[j]->name);
			printf("\n\n");
		}
		j = 0;
		// (*tmp)->dead_end = 1;
		if (DEBUG == 1)
			printf("dead end %s %d\n", (*tmp)->name, (*tmp)->is_junction);
		if ((*tmp)->neighbours[j] == prev)
			j++;
		prev = *tmp;
		if (j < (*tmp)->neighbours_len)
			*tmp = (*tmp)->neighbours[j];
		else
			break;
	}
	remove_dead_end_from_nbs(prev, map);
}

static void		flag_conj(t_map *map)
{
	size_t	i;
	t_room	*tmp;

	i = 0;
	while (i < map->rooms->size)
	{
		if (map->rooms->entries[i] != NULL)
		{
			tmp = ((t_room *)map->rooms->entries[i]->val);
			if (is_junction(tmp, map) == 1)
				tmp->is_junction = 1;
		}
		i++;
	}
}

static void		remove_dead_ends(t_map *map, int *changed)
{
	size_t	i;
	t_room	*tmp;

	i = 0;
	while (i < map->rooms->size)
	{
		if (map->rooms->entries[i] != NULL)
		{
			tmp = ((t_room *)map->rooms->entries[i]->val);
			if (tmp != map->start && tmp != map->end)
			{
				// printf("candidate %s\n", tmp->name);
				if (is_dead_end_first(tmp) == 1)
				{
					*changed = 1;
					if (DEBUG == 1)
						printf("Dead end first %s\n", tmp->name);
					remove_dead_path(&tmp, map);
				}
			}
		}
		i++;
	}
}

void			remove_sps_spe_conns(t_map *map)
{
	size_t	i;
	size_t	j;
	t_room	*tmp;

	i = 0;
	j = 0;
	while (i < map->rooms->size)
	{
		if (((t_entry *)map->rooms->entries[i]) != NULL)
		{
			tmp = ((t_room *)map->rooms->entries[i]->val);
			if (tmp->sps == 1 && tmp != map->start)
			{
				j = 0;
				while (j < tmp->neighbours_len)
				{
					if (tmp->neighbours[j] != NULL
					&& tmp->neighbours[j]->sps == 1
					&& tmp->neighbours[j] != map->start)
						j -= del_tube(tmp, tmp->neighbours[j], map);
					j++;
				}
			}
			if (tmp->spe == 1 && tmp != map->end)
			{
				j = 0;
				while (j < tmp->neighbours_len)
				{
					if (tmp->neighbours[j] != NULL
					&& tmp->neighbours[j]->spe == 1
					&& tmp->neighbours[j] != map->end)
						j -= del_tube(tmp, tmp->neighbours[j], map);
					j++;
				}
			}
		}
		i++;
	}
}

ssize_t			sanitize_input(t_map *map)
{
	t_room *tmp;
	int		changed;

	if (DEBUG == 1)
		printf("Sanitize input\n");
	changed = 1;
	if (map->rooms == NULL)
		return (parse_error(8));
	if (map->start == NULL)
		return (parse_error(9));
	if (map->end == NULL)
		return (parse_error(10));
	tmp = (t_room *)search_ht(map->rooms, map->start->name);
	if (tmp->neighbours == NULL)
		return (parse_error(11));
	tmp = (t_room *)search_ht(map->rooms, map->end->name);
	if (tmp->neighbours == NULL)
		return (parse_error(12));
	flag_conj(map);
	remove_sps_spe_conns(map);
	while (changed == 1)
	{
		changed = 0;
		remove_dead_ends(map, &changed);
		if (map->start->neighbours_len == 0 ||
			map->end->neighbours_len == 0)
		{
			if (DEBUG == 1)
				printf("No connections from start or end\n");
			return (EXIT_FAILURE);
		}
		flag_conj(map);
		remove_unnecessary_tubes(map, &changed);
		flag_conj(map);
	}
	if (DEBUG == 1)
	{
		print_map(map);
		exit (0);
	}
	if (map->start->neighbours_len == 0 ||
	map->end->neighbours_len == 0)
		return (EXIT_FAILURE);
	printf("Ok\n");
	exit (0);
	return (EXIT_SUCCESS);
}

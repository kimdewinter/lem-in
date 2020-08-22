/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   un_find_real_nb.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 16:32:48 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/20 19:26:43 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int		find_next(t_connection *tmp, t_room **curr, t_room **nb,
int *found)
{
	if (*nb != tmp->dst_nb
	&& *nb != tmp->dst
	&& room_in_bitfield(*nb, (*curr)->unavailable) == 0)
	{
		if ((*nb)->is_junction == 0)
		{
			*found = 1;
			tmp->dist++;
		}
		tmp->dst_nb = *curr;
		*curr = *nb;
	}
	if ((*found == 0 && (*curr)->is_junction == 1) || *found == 1)
		return (0);
	return (1);
}

static int		check_found(int found, t_connection *tmp, t_room *nb)
{
	if (found == 0 && nb->is_junction == 0)
	{
		tmp->dst = NULL;
		return (0);
	}
	return (1);
}

void			find_real_nb(t_connection *tmp)
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
			if (find_next(tmp, &nb, &(nb->neighbours[i]), &found) == 0)
				break ;
			i++;
		}
		if (check_found(found, tmp, nb) == 0)
			return ;
	}
	tmp->dst = nb;
}

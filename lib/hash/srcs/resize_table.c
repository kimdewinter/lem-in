/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   resize_table.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 11:06:46 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/05 13:57:20 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hashing.h"

static int		resize_table(t_table **ht, int base_size)
{
	t_table	*new_table;
	int		i;
	int		index;

	if (base_size < BASE_SIZE)
		return (1);
	new_table = create_ht(base_size);
	if (!new_table)
		return (0);
	i = 0;
	while (i < (*ht)->size)
	{
		if ((*ht)->entries[i] != NULL)
		{
			index = rehash(((t_entry *)(*ht)->entries[i])->key, new_table);
			new_table->entries[index] = (*ht)->entries[i];
		}
		i++;
	}
	new_table->count = (*ht)->count;
	free ((*ht)->entries);
	free (*ht);
	*ht = NULL;
	*ht = new_table;
	return (1);
}

int		resize_up(t_table **ht)
{
	int		new_size;

	new_size = (*ht)->base_size * 2;
	if (!resize_table(ht, new_size))
		return (0);
	return (1);
}

int		resize_down(t_table **ht)
{
	int		new_size;

	new_size = (*ht)->base_size / 2;
	if (!resize_table(ht, new_size))
		return (0);
	return (1);
}
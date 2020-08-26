/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   resize_table.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 11:06:46 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/26 10:38:39 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hashing.h"

static void	set_new_values(t_table *ht, t_table *new_table,
int tmp_size, t_entry **tmp_entr)
{
	ht->base_size = new_table->base_size;
	ht->count = new_table->count;
	tmp_size = ht->size;
	ht->size = new_table->size;
	new_table->size = tmp_size;
	tmp_entr = ht->entries;
	ht->entries = new_table->entries;
	new_table->entries = tmp_entr;
	delete_ht(new_table);
}

static int	resize_table(t_table *ht, unsigned long long base_size)
{
	t_table	*new_table;
	int		i;
	int		tmp_size;
	t_entry	**tmp_entr;

	if (base_size < BASE_SIZE)
		return (1);
	new_table = create_ht(base_size);
	if (!new_table)
		return (0);
	i = 0;
	while (i < ht->size)
	{
		if (ht->entries[i] != NULL)
			insert_ht(new_table, ht->entries[i]->key, ht->entries[i]->val);
		i++;
	}
	set_new_values(ht, new_table, tmp_size, tmp_entr);
	return (1);
}

int			resize_up(t_table *ht)
{
	int		new_size;

	new_size = ht->base_size * 2;
	if (!resize_table(ht, new_size))
		return (0);
	return (1);
}

int			resize_down(t_table *ht)
{
	int		new_size;

	new_size = ht->base_size / 2;
	if (!resize_table(ht, new_size))
		return (0);
	return (1);
}

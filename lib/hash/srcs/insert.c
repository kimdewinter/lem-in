/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   insert.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 12:32:48 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/08 14:15:00 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hashing.h"

int		insert_ht(t_table *ht, char *key, void *value)
{
	t_entry	*item;
	int		index;
	int		i;
	int		load;

	load = (ht->count * 100) / ht->size;
	if (load > 70)
		resize_up(&ht);
	item = new_entry(key, value);
	if (!item)
		return (0);
	i = 0;
	index = get_hash(key, ht, i);
	while (ht->entries[index] != NULL)
	{
		i++;
		index = get_hash(key, ht, i);
	}
	ht->entries[index] = item;
	ht->count++;
	return (1);
}
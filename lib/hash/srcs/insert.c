/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   insert.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 12:32:48 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/13 13:54:28 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hashing.h"

ssize_t	insert_ht(t_table *ht, char *key, void *value)
{
	t_entry	*item;
	unsigned long long		index;
	unsigned long long		prev_index;
	int		i;
	int		load;

	load = (ht->count * 100) / ht->size;
	if (load > 70)
		resize_up(ht);
	item = new_entry(key, value);
	if (!item)
		return (EXIT_FAILURE);
	i = 0;
	index = get_hash(key, ht, i) % ht->size;
	while (ht->entries[index] != NULL)
	{
		i++;
		prev_index = index;
		index = get_hash(key, ht, i);
	}
	ht->entries[index] = item;
	ht->count++;
	return (EXIT_SUCCESS);
}

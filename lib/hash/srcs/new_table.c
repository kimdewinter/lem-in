/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_table.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 20:44:50 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/08 15:55:06 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hashing.h"

t_table		*create_ht(size_t size)
{
	t_table *ht;

	ht = (t_table *)malloc(sizeof(t_table));
	if (ht)
	{
		ht->base_size = size;
		ht->size = next_prime(size);
		ht->count = 0;
		ht->entries = malloc(sizeof(t_entry) * ht->size);
		if (ht->entries)
			memset(ht->entries, 0, ht->size * sizeof(t_entry));
	}
	return (ht);
}
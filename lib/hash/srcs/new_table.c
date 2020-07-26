/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_table.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 20:44:50 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/13 13:55:44 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hashing.h"

t_table		*create_ht(size_t size)
{
	t_table *ht;
	size_t	real_size;

	ht = (t_table *)malloc(sizeof(t_table));
	if (ht)
	{
		if (size < BASE_SIZE)
			real_size = BASE_SIZE;
		else
			real_size = size;
		ht->base_size = real_size;
		ht->size = next_prime(real_size);
		ht->count = 0;
		ht->entries = (t_entry **)malloc(sizeof(t_entry *) * ht->size);
		if (ht->entries)
			memset(ht->entries, 0, ht->size * sizeof(t_entry *));
	}
	return (ht);
}
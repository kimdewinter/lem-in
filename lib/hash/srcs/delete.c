/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 21:20:00 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/08 14:33:41 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hashing.h"

static void	delete_entry(t_entry *entry, void (*del_ptr)(void *))
{
	free (entry->key);
	del_ptr(entry->val);
	free (entry);
}

void	delete_ht(t_table *ht, void (*del_ptr)(void *))
{
	int	i;

	i = 0;
	while (i < ht->size)
	{
		if (ht->entries[i])
			delete_entry(ht->entries[i], del_ptr);
		i++;
	}
	free (ht->entries);
	free (ht);
}
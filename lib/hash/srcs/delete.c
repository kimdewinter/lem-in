/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 21:20:00 by lravier       #+#    #+#                 */
/*   Updated: 2020/10/01 12:04:47 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hashing.h"

static void	delete_entry(t_entry *entry)
{
	if (entry->key)
		free(entry->key);
	free(entry);
	entry = NULL;
}

void		delete_ht(t_table *ht)
{
	size_t	i;

	i = 0;
	while (i < ht->size)
	{
		if (ht->entries[i] != NULL)
			delete_entry(ht->entries[i]);
		i++;
	}
	free(ht->entries);
	free(ht);
}

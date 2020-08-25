/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 20:37:32 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/25 17:23:23 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hashing.h"

void	*search_ht(t_table *ht, char *key)
{
	int		index;
	t_entry *item;
	int		i;

	i = 0;
	index = get_hash(key, ht, i);
	item = ht->entries[index];
	while (item != NULL)
	{
		if (ft_strcmp(item->key, key) == 0)
			return (item->val);
		i++;
		index = get_hash(key, ht, i);
		item = ht->entries[index];
	}
	return (NULL);
}

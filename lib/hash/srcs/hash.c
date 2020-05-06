/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hash.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 20:10:53 by lravier       #+#    #+#                 */
/*   Updated: 2020/04/30 17:37:23 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hashing.h"

unsigned	hash(char *key, int prime, int size)
{
	size_t i;
	long long unsigned hash;
	size_t len;

	hash = 0;
	len = ft_strlen(key);
	i = 0;
	while (i < len)
	{
		hash += ft_pow_ll(prime, len - (i + 1)) * key[i];
		hash = hash % size;
		i++;
	}
	return ((unsigned)hash);
}

unsigned	get_hash(char *key, t_table *ht, int attempt)
{
	int		hash_a;
	int		hash_b;

	hash_a = hash(key, PRIME_A, ht->size);
	hash_b = hash(key, PRIME_B, ht->size);
	return (((unsigned)hash_a + (attempt * (hash_b + 1))) % ht->size);
}

unsigned	rehash(char *key, t_table *new_table)
{
	int				i;
	unsigned		ind;

	ind = get_hash(key, new_table, 0);
	i = 1;
	while (new_table->entries[ind] != NULL)
	{
		ind = get_hash(key, new_table, i);
		i++;
	}
	return (ind);
}
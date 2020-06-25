/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hash.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 20:10:53 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/13 13:55:27 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hashing.h"

unsigned long long	hash(char *key, long long unsigned size)
{
	size_t i;
	long long unsigned hash;
	size_t len;

	hash = 0;
	len = ft_strlen(key);
	i = 0;
	while (i < len)
	{
		hash = key[i] + (hash << 6) + (hash << 16) - hash;
		i++;
	}
	return (hash % size);
}

unsigned long long	get_hash(char *key, t_table *ht, int attempt)
{
	unsigned long long hash_a;
	unsigned long long hash_b;
	unsigned long long res;

	hash_a = hash(key, ht->size);
	hash_b = hash(key, ht->size - 1);
	res = (hash_a + (attempt * (hash_b + 1))) % ht->size;
	return (res);
}
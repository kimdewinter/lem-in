/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 19:51:36 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/25 14:11:17 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHING_H
# define HASHING_H
# define BASE_SIZE 1000
# define KEY r_name
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "../../libft/libft.h"
# include "../../libft/get_next_line.h"

typedef struct 	s_entry
{
	char	*key;
	void	*val;
}				t_entry;

typedef struct	s_table
{
	unsigned long long	base_size;
	unsigned long long	size;
	unsigned long long	count;
	t_entry				**entries;
}				t_table;

t_table				*create_ht(size_t size);
int					next_prime(int n);
long long unsigned	ft_pow_ll(unsigned long long base, unsigned long long pow);
long long unsigned	get_hash(char *key, t_table *ht, int attempt);
unsigned long long	hash(char *key, unsigned long long prime);
ssize_t				insert_ht(t_table *ht, char *key, void *value);
int					resize_up(t_table *ht);
int					resize_down(t_table *ht);
t_entry				*new_entry(char *key, void *value);
void				*search_ht(t_table *ht, char *key);
void				delete_ht(t_table *ht);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 19:51:36 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/23 19:21:07 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHING_H
# define HASHING_H
# define BASE_SIZE 50
# define PRIME_A 151
# define PRIME_B 163
// # define VAL_T t_room *
# define KEY r_name
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "../../libft/libft.h"
# include "../../libft/get_next_line.h"
# include "../../../includes/lemin.h"

typedef struct 	s_entry
{
	char	*key;
	void	*val;
}				t_entry;

typedef struct	s_table
{
	int					base_size;
	int					size;
	int 				count;
	t_entry				**entries;
}				t_table;

t_table				*create_ht(size_t size);
int					next_prime(int n);
long long unsigned	ft_pow_ll(int base, int pow);
unsigned			get_hash(char *key, t_table *ht, int attempt);
unsigned			rehash(char *key, t_table *new_table);
ssize_t				insert_ht(t_table *ht, char *key, void *value);
int					resize_up(t_table **ht);
int					resize_down(t_table **ht);
t_entry				*new_entry(char *key, void *value);
void				*search_ht(t_table *ht, char *key);
#endif
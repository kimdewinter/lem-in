/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_item.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 21:13:50 by lravier       #+#    #+#                 */
/*   Updated: 2020/04/30 17:37:41 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hashing.h"

t_entry *new_entry(char *key, void *value)
{
	t_entry *tmp;

	tmp = (t_entry *)malloc(sizeof(t_entry));
	if (!tmp)
		return(NULL);
	tmp->key = strdup(key);
	tmp->val = value;
	if (!tmp->key)
		return (NULL);
	return (tmp);
}
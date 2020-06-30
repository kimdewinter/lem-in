/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_map.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 14:12:09 by kim           #+#    #+#                 */
/*   Updated: 2020/06/30 14:24:32 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		clean_map(t_map *map)
{
	map->antmount = -1;
	map->start = NULL;
	map->end = NULL;
	//PLACEHOLDER: the inside of rooms must be cleaned before the delete_ht call
	delete_ht(map->rooms);
	map->rooms = NULL;
	delete_all_routes(map->routes, map);
}
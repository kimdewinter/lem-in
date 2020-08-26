/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_rooms.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 17:46:14 by kim           #+#    #+#                 */
/*   Updated: 2020/08/26 15:13:17 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t			check_duplicate_room(const char *room_name, const t_map *map)
{
	if (search_ht(map->rooms, (char *)room_name) == NULL)
		return (EXIT_SUCCESS);
	else
	{
		ft_printf("Error: duplicate room name.\n");
		return (EXIT_FAILURE);
	}
}

static size_t	setup_bitrooms(t_map *map)
{
	unsigned long long	i;
	t_table				*table;
	t_room				*tmp;

	i = 0;
	table = map->rooms;
	while (i < table->size)
	{
		if (table->entries[i] != NULL)
		{
			tmp = (t_room *)table->entries[i]->val;
			if (bite_room_new(tmp, map) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static ssize_t	parse_options(t_input_reader *input, t_map *map, size_t *i,
size_t *num_room)
{
	if (is_room(input->lines[*i]) == 1)
	{
		if (add_room(input->lines[*i], map, num_room) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (is_comment(input->lines[*i]) == 3)
	{
		if (add_special_room(input, map, i, num_room) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (is_comment(input->lines[*i]) == 2)
	{
		if (add_special_room(input, map, i, num_room) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (is_tube(input->lines[*i], map) == 1)
	{
		map->bitfield_len = map->rooms->count / BITFIELD_SIZE + 1;
		if (setup_bitrooms(map) == EXIT_SUCCESS)
			return (EXIT_IS_TUBE);
		return (parse_error(14));		
	}
	else if (is_comment(input->lines[*i]) != 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

ssize_t			parse_rooms(t_input_reader *input, t_map *map, size_t *i)
{
	size_t	num_room;
	size_t	is_tube;

	num_room = 1;
	is_tube = EXIT_SUCCESS;
	if (input != NULL && map != NULL)
	{
		while (*i < input->num_lines && input->lines[*i] != NULL &&
				is_tube == EXIT_SUCCESS)
		{
			is_tube = parse_options(input, map, i, &num_room);
			if (is_tube == EXIT_IS_TUBE)
				return (EXIT_SUCCESS);
			if (is_tube == EXIT_FAILURE)
				return (EXIT_FAILURE);
			// if (is_tube(input->lines[*i]) == 1)
			// {
			// 	map->bitfield_len = map->rooms->count / BITFIELD_SIZE + 1;
			// 	if (setup_bitrooms(map) == EXIT_SUCCESS)
			// 		return (EXIT_SUCCESS);
			// 	return (parse_error(14));
			// }
			// else
			// {
			// 	if (parse_options(input, map, i, &num_room) == EXIT_FAILURE)
			// 		return (EXIT_FAILURE);
			// }
			(*i)++;
		}
	}
	return (parse_error(7));
}

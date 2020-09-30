/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_rooms.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 17:46:14 by kim           #+#    #+#                 */
/*   Updated: 2020/09/30 16:49:07 by simoncleerd   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t			check_duplicate_room(const char *room_name, const t_map *map)
{
	if (search_ht(map->rooms, (char *)room_name) == NULL)
		return (EXIT_SUCCESS);
	else
		return (parse_error(18));
}

static ssize_t	parse_options(t_input_reader *input, t_map *map, size_t *i)
{
	if (is_room(input->lines[*i]) == 1)
	{
		if (add_room(input, i, map, 0) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (is_comment(input->lines[*i]) == 3 ||
	is_comment(input->lines[*i]) == 2)
	{
		if (add_special_room(input, map, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (is_comment(input->lines[*i]) != 1)
		return (parse_error(17));
	return (EXIT_SUCCESS);
}

ssize_t			parse_rooms(t_input_reader *input, t_map *map, size_t *i)
{
	if (input != NULL && map != NULL)
	{
		while (*i < input->num_lines && input->lines[*i] != NULL)
		{
			if (is_tube(input->lines[*i]) == 1)
			{
				map->bitfield_len = map->rooms->count / BITFIELD_SIZE + 1;
				return (EXIT_SUCCESS);
			}
			else
			{
				if (parse_options(input, map, i) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			(*i)++;
		}
	}
	return (parse_error(7));
}

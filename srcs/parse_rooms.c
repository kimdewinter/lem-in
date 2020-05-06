/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_rooms.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 17:46:14 by kim           #+#    #+#                 */
/*   Updated: 2020/05/06 17:46:16 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static ssize_t	add_room_special(t_input_reader *input, t_map *map, size_t *i)
{
	char	**words;
	t_room	*room;

	if (is_room(input->lines[*i + 1]) == 1)
	{
		words = ft_strsplit(input->lines[*i + 1], ' ');
		if (words[0] != NULL && words[1] != NULL && words[2] != NULL)
			if (setup_room(&room, words[0], words[1], words[2]) == EXIT_SUCCESS)
				if (insert_ht(map->rooms, room->name, room) == EXIT_SUCCESS)
				{
					if (is_comment(input->lines[*i]) == 2)
						map->start = search_ht(map->rooms, room->name);
					else if (is_comment(input->lines[*i] == 3))
						map->end = search_ht(map->rooms, room->name);
					*i++;
					return (EXIT_SUCCESS);
				}
	}
	return (EXIT_FAILURE);
}

static ssize_t	add_room(const char *line, t_map *map)
{
	char	**words;
	t_room	*room;

	words = ft_strsplit(line, ' ');
	if (words[0] != NULL && words[1] != NULL && words[2] != NULL)
		if (setup_room(&room, words[0], words[1], words[2]) == EXIT_SUCCESS)
			if (insert_ht(map->rooms, room->name, room) == EXIT_SUCCESS)
				return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

ssize_t	parse_rooms(t_input_reader *input, t_map *map, size_t *i)
{
	if (input != NULL && map != NULL)
	{
		while (i < input->num_lines && input->lines[*i] != NULL)
		{
			if (is_tube(input->lines[*i] == 1))
				return (EXIT_SUCCESS);
			else if (is_room(input->lines[*i]) == 1)
				if (add_room(input->lines[*i], map) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			else if (is_comment(input->lines[*i] == 3))
				if (add_special_room(input, map, i) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			else if (is_comment(input->lines[*i] == 2))
				if (add_special_room(input, map, i) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			else if (is_comment(input->lines[*i] != 1))
				return (EXIT_FAILURE);
			*i++;
		}
	}
	return (EXIT_FAILURE);
}

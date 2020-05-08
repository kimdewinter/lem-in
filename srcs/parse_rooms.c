/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_rooms.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 17:46:14 by kim           #+#    #+#                 */
/*   Updated: 2020/05/08 15:55:06 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static ssize_t	get_coords(char *wordx, char *wordy, size_t *posx, size_t *posy)
{
	size_t	overflow;

	overflow = 0;
	*posx = ft_atoi_ll(wordx, &overflow);
	if (overflow == 0)
	{
		*posy = ft_atoi_ll(wordy, &overflow);
		if (overflow == 0)
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static ssize_t	add_special_room(t_input_reader *input, t_map *map, size_t *i)
{
	char	**words;
	t_room	*room;
	size_t	posx;
	size_t	posy;

	if (is_room(input->lines[*i + 1]) == 1)//NOTE: this does not allow comments between ##start and the room-line that comes after; correct?
	{
		words = ft_strsplit(input->lines[*i + 1], ' ');
		if (words[0] != NULL && words[1] != NULL && words[2] != NULL)
			if (get_coords(words[1], words[2], &posx, &posy) == EXIT_SUCCESS)
				if (setup_room(&room, words[0], posx, posy) == EXIT_SUCCESS)
					if (insert_ht(map->rooms, room->name, room) == EXIT_SUCCESS)
					{
						if (is_comment(input->lines[*i]) == 2)
							map->start = ft_strdup(room->name);
						else if (is_comment(input->lines[*i]) == 3)
							map->end = ft_strdup(room->name);
						(*i)++;
						return (EXIT_SUCCESS);
					}
	}
	return (EXIT_FAILURE);
}

static ssize_t	add_room(const char *line, t_map *map)
{
	char	**words;
	t_room	*room;
	size_t	posx;
	size_t	posy;

	words = ft_strsplit(line, ' ');
	if (words[0] != NULL && words[1] != NULL && words[2] != NULL)
		if (get_coords(words[1], words[2], &posx, &posy) == EXIT_SUCCESS)
			if (setup_room(&room, words[0], posx, posy) == EXIT_SUCCESS)
				if (insert_ht(map->rooms, room->name, room) == EXIT_SUCCESS)
					return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

ssize_t	parse_rooms(t_input_reader *input, t_map *map, size_t *i)
{
	if (input != NULL && map != NULL)
	{
		while (*i < input->num_lines && input->lines[*i] != NULL)
		{
			if (is_tube(input->lines[*i]) == 1)
				return (EXIT_SUCCESS);
			else if (is_room(input->lines[*i]) == 1)
			{
				if (add_room(input->lines[*i], map) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else if (is_comment(input->lines[*i]) == 3)
			{
				if (add_special_room(input, map, i) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else if (is_comment(input->lines[*i]) == 2)
			{
				if (add_special_room(input, map, i) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else if (is_comment(input->lines[*i]) != 1)
				return (EXIT_FAILURE);
			(*i)++;
		}
	}
	return (EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_rooms_add_room.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 13:43:23 by lravier       #+#    #+#                 */
/*   Updated: 2020/09/30 17:28:22 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t		get_coords(char *wordx, char *wordy)
{
	int			overflow;
	int			result;

	overflow = 0;
	result = atoi_overflow(wordx, &overflow);
	if (overflow == 0 && (result >= INT_MIN && result <= INT_MAX))
	{
		result = atoi_overflow(wordy, &overflow);
		if (overflow == 0 && (result >= INT_MIN && result <= INT_MAX))
		{
			return (EXIT_SUCCESS);
		}
	}
	return (parse_error(16));
}

static ssize_t		free_and_return(char ***words, ssize_t ret)
{
	if (*words != NULL)
	{
		if ((*words)[0] != NULL)
			free((*words)[0]);
		if ((*words)[1] != NULL)
			free((*words)[1]);
		if ((*words)[2] != NULL)
			free((*words)[2]);
		free(*words);
		*words = NULL;
	}
	return (ret);
}

static ssize_t		sse_room(size_t *i, t_room *room, t_input_reader
*input, t_map *map)
{
	if (is_comment(input->lines[*i]) == 2)
	{
		if (map->start != NULL)
			return (parse_error(21));
		map->start = search_ht(map->rooms, room->name);
		map->start->dist_to_start = 0;
	}
	else if (is_comment(input->lines[*i]) == 3)
	{
		if (map->end != NULL)
			return (parse_error(22));
		map->end = search_ht(map->rooms, room->name);
		map->end->dist_to_end = 0;
	}
	(*i)++;
	return (EXIT_SUCCESS);
}

ssize_t				add_special_room(t_input_reader *input,
									t_map *map,
									size_t *i)
{
	if (is_room(input->lines[*i + 1]) == 1)
	{
		if (add_room(input, i, map, 1) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	return (parse_error(20));
}

ssize_t				add_room(t_input_reader *input, size_t *i, t_map *map,
int special)
{
	char	**words;
	t_room	*room;

	room = NULL;
	if (special == 1)
		words = ft_strsplit(input->lines[*i + 1], ' ');
	else
		words = ft_strsplit(input->lines[*i], ' ');
	if (words != NULL && words[0] != NULL && words[1] != NULL &&
	words[2] != NULL)
	{
		if (check_duplicate_room(words[0], map) == EXIT_FAILURE)
			return (free_and_return(&words, EXIT_FAILURE));
		if (get_coords(words[1], words[2]) == EXIT_FAILURE)
			return (free_and_return(&words, EXIT_FAILURE));
		if (setup_room(&room, words[0], map->rooms->count + 1) == EXIT_FAILURE)
			return (free_and_return(&words, parse_error(23)));
		if (insert_ht(map->rooms, room->name, room) == EXIT_FAILURE)
			return (free_and_return(&words, parse_error(23)));
		if (special == 1)
			return (free_and_return(&words, sse_room(i, room, input, map)));
		return (free_and_return(&words, EXIT_SUCCESS));
	}
	return (free_and_return(&words, parse_error(23)));
}

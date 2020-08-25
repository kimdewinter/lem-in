/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_rooms_add_room.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 13:43:23 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/25 16:13:03 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	get_coords(char *wordx, char *wordy)
{
	size_t	overflow;

	overflow = 0;
	ft_atoi_ll(wordx, &overflow);
	if (overflow == 0)
	{
		ft_atoi_ll(wordy, &overflow);
		if (overflow == 0)
		{
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

static ssize_t	free_and_return(char ***words, ssize_t ret)
{
	if (*words != NULL)
	{
		if (ret == EXIT_FAILURE)
			free((*words)[0]);
		free ((*words)[1]);
		free((*words)[2]);
		free(*words);
		*words = NULL;
	}
	return (ret);
}

static void		set_start_end_room(size_t *i, t_room *room, t_input_reader
*input, t_map *map)
{
	if (is_comment(input->lines[*i]) == 2)
	{
		map->start = search_ht(map->rooms, room->name);
		map->start->dist_to_start = 0;
	}
	else if (is_comment(input->lines[*i]) == 3)
	{
		map->end = search_ht(map->rooms, room->name);
		map->end->dist_to_end = 0;
	}
	(*i)++;
}

ssize_t			add_special_room(t_input_reader *input,
									t_map *map,
									size_t *i,
									size_t *num_room)
{
	char	**words;
	t_room	*room;

	words = NULL;
	if (is_room(input->lines[*i + 1]) == 1)
	{
		words = ft_strsplit(input->lines[*i + 1], ' ');
		if (words[0] != NULL && words[1] != NULL && words[2] != NULL)
			if (check_duplicate_room(words[0], map) == EXIT_SUCCESS)
				if (get_coords(words[1], words[2]) ==
					EXIT_SUCCESS)
					if (setup_room(&room, words[0], num_room) ==
						EXIT_SUCCESS)
						if (insert_ht(map->rooms, room->name, room) ==
							EXIT_SUCCESS)
						{
							set_start_end_room(i, room, input, map);
							(*num_room)++;
							return (free_and_return(&words, EXIT_SUCCESS));
						}
	}
	return (free_and_return(&words, EXIT_FAILURE));
}

ssize_t			add_room(const char *line, t_map *map, size_t *num_room)
{
	char	**words;
	t_room	*room;

	words = ft_strsplit(line, ' ');
	if (words[0] != NULL && words[1] != NULL && words[2] != NULL)
		if (check_duplicate_room(words[0], map) == EXIT_SUCCESS)
			if (get_coords(words[1], words[2]) == EXIT_SUCCESS)
				if (setup_room(&room, words[0], num_room) ==
					EXIT_SUCCESS)
					if (insert_ht(map->rooms, room->name, room) == EXIT_SUCCESS)
					{
						(*num_room)++;
						return (free_and_return(&words, EXIT_SUCCESS));
					}
	return (free_and_return(&words, EXIT_FAILURE));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_rooms.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 17:46:14 by kim           #+#    #+#                 */
/*   Updated: 2020/08/09 11:58:17 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	check_duplicate_room(const char *room_name, const t_map *map)
{
	if (search_ht(map->rooms, (char *)room_name) == NULL)
		return (EXIT_SUCCESS);
	else
	{
		ft_printf("Error: duplicate room name.\n");
		return (EXIT_FAILURE);
	}
}

static ssize_t	get_coords(char *wordx, char *wordy, size_t *posx, size_t *posy)
{
	size_t	overflow;

	overflow = 0;
	*posx = ft_atoi_ll(wordx, &overflow);
	if (overflow == 0)
	{
		free(wordx);
		*posy = ft_atoi_ll(wordy, &overflow);
		if (overflow == 0)
		{
			free(wordy);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

static ssize_t	add_special_room(t_input_reader *input,
									t_map *map,
									size_t *i,
									size_t *num_room)
{
	char	**words;
	t_room	*room;
	size_t	posx;
	size_t	posy;

	words = NULL;
	if (is_room(input->lines[*i + 1]) == 1)
	{
		words = ft_strsplit(input->lines[*i + 1], ' ');
		if (words[0] != NULL && words[1] != NULL && words[2] != NULL)
			if (check_duplicate_room(words[0], map) == EXIT_SUCCESS)
				if (get_coords(words[1], words[2], &posx, &posy) ==
					EXIT_SUCCESS)
					if (setup_room(&room, words[0], posx, posy, num_room) ==
						EXIT_SUCCESS)
						if (insert_ht(map->rooms, room->name, room) ==
							EXIT_SUCCESS)
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
							(*num_room)++;
							free(words);
							return (EXIT_SUCCESS);
						}
	}
	free(words);
	return (EXIT_FAILURE);
}

static ssize_t	add_room(const char *line, t_map *map, size_t *num_room)
{
	char	**words;
	t_room	*room;
	size_t	posx;
	size_t	posy;

	words = ft_strsplit(line, ' ');
	if (words[0] != NULL && words[1] != NULL && words[2] != NULL)
		if (check_duplicate_room(words[0], map) == EXIT_SUCCESS)
			if (get_coords(words[1], words[2], &posx, &posy) == EXIT_SUCCESS)
				if (setup_room(&room, words[0], posx, posy, num_room) ==
					EXIT_SUCCESS)
					if (insert_ht(map->rooms, room->name, room) == EXIT_SUCCESS)
					{
						(*num_room)++;
						free(words);
						return (EXIT_SUCCESS);
					}
	free(words);
	return (EXIT_FAILURE);
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
			if (bite_room_new(tmp, map) == EXIT_FAILURE
			|| bite_alloc(&tmp->removed_conns, map) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

ssize_t			parse_rooms(t_input_reader *input, t_map *map, size_t *i)
{
	size_t	num_room;

	num_room = 1;
	if (input != NULL && map != NULL)
	{
		while (*i < input->num_lines && input->lines[*i] != NULL)
		{
			if (is_tube(input->lines[*i]) == 1)
			{
				map->bitfield_len = map->rooms->count / BITFIELD_SIZE + 1;
				if (setup_bitrooms(map) == EXIT_SUCCESS)
					return (EXIT_SUCCESS);
				return (parse_error(14));
			}
			else if (is_room(input->lines[*i]) == 1)
			{
				if (add_room(input->lines[*i], map, &num_room) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else if (is_comment(input->lines[*i]) == 3)
			{
				if (add_special_room(input, map, i, &num_room) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else if (is_comment(input->lines[*i]) == 2)
			{
				if (add_special_room(input, map, i, &num_room) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else if (is_comment(input->lines[*i]) != 1)
				return (EXIT_FAILURE);
			(*i)++;
		}
	}
	return (parse_error(7));
}

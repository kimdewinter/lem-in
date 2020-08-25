/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_tubes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 15:39:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/25 17:05:48 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int		check_duplicate_tube(t_room *room1, t_room *room2)
{
	size_t	i;

	i = 0;
	while (i < room1->neighbours_len)
	{
		if (room1->neighbours[i] == room2)
			return (1);
		i++;
	}
	return (0);
}

static int		add_tubes(t_map *map, char **rooms)
{
	t_room *room1;
	t_room *room2;

	room1 = (t_room *)search_ht(map->rooms, rooms[0]);
	room2 = (t_room *)search_ht(map->rooms, rooms[1]);
	if (room1 == NULL || room2 == NULL)
		return (0);
	if (check_duplicate_tube(room1, room2) == 1)
		return (15);
	if (add_neighbour(room1, room2) == EXIT_FAILURE)
		return (0);
	if (add_neighbour(room2, room1) == EXIT_FAILURE)
		return (0);
	return (1);
}

static void		parse_tube_loop(int *dash, const char *line)
{
	size_t	i;

	*dash = 0;
	i = 0;
	while (line[i])
	{
		i++;
		if (line[i] == '-')
			*dash += 1;
	}
}

static size_t	parse_tube(char *line, t_map *map, size_t *tubes)
{
	char	**rooms;
	int		dash;
	size_t	error;

	parse_tube_loop(&dash, line);
	if (dash != 1)
		return (4);
	rooms = ft_strsplit(line, '-');
	if (!rooms)
		return (5);
	error = add_tubes(map, rooms);
	if (error != 1)
	{
		free_room_names(rooms);
		return (error);
	}
	(*tubes)++;
	free_room_names(rooms);
	return (1);
}

ssize_t			parse_tubes(t_input_reader *input, t_map *map, size_t *i)
{
	size_t		tubes;
	size_t		error;

	tubes = 0;
	while (*i < input->num_lines)
	{
		if (is_comment(input->lines[*i]) == 0)
		{
			error = parse_tube(input->lines[*i], map, &tubes);
			if (error != 1)
				return (parse_error(error));
		}
		(*i)++;
	}
	if (tubes == 0)
		return (parse_error(7));
	return (EXIT_SUCCESS);
}

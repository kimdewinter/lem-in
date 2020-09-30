/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_tubes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 15:39:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/09/30 15:25:52 by lravier       ########   odam.nl         */
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

static ssize_t		add_tubes(t_map *map, char **rooms)
{
	t_room *room1;
	t_room *room2;

	room1 = (t_room *)search_ht(map->rooms, rooms[0]);
	room2 = (t_room *)search_ht(map->rooms, rooms[1]);
	if (room1 == NULL || room2 == NULL)
		return (parse_error(19));
	if (check_duplicate_tube(room1, room2) == 1)
		return (parse_error(15));
	if (add_neighbour(room1, room2) == EXIT_FAILURE)
		return (parse_error(23));
	if (add_neighbour(room2, room1) == EXIT_FAILURE)
		return (parse_error(23));
	return (EXIT_SUCCESS);
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

static ssize_t	parse_tube(char *line, t_map *map, size_t *tubes)
{
	char	**rooms;
	int		dash;
	ssize_t	error;

	parse_tube_loop(&dash, line);
	if (dash != 1)
		return (parse_error(4));
	rooms = ft_strsplit(line, '-');
	if (!rooms)
		return (parse_error(5));
	error = add_tubes(map, rooms);
	if (error == EXIT_FAILURE)
	{
		free_room_names(rooms);
		return (error);
	}
	(*tubes)++;
	free_room_names(rooms);
	return (EXIT_SUCCESS);
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
			if (error != EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
		(*i)++;
	}
	if (tubes == 0)
		return (parse_error(7));
	return (EXIT_SUCCESS);
}

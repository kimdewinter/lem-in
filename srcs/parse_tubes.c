/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_tubes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 15:39:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/25 15:30:10 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static	void		set_spe_sps(t_map *map, t_room *room1, t_room *room2)
{
	if (room1 == map->start)
		room2->sps = 1;
	if (room1 == map->end)
		room2->spe = 1;
	if (room2 == map->start)
		room1->sps = 1;
	if (room2 == map->end)
		room1->spe = 1;
}

static int			check_duplicate_tube(t_room *room1, t_room *room2)
{
	size_t	i;

	i = 0;
	while (i < room1->neighbours_len)
	{
		if (room1->neighbours[i] == room2)
			return (1);
		i++;
	}
	i = 0;
	while (i < room2->neighbours_len)
	{
		if (room2->neighbours[i] == room1)
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
		return (EXIT_FAILURE);
	if (check_duplicate_tube(room1, room2) == 1)
		return (parse_error(15));
	if (add_neighbour(room1, room2) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (add_neighbour(room2, room1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	set_spe_sps(map, room1, room2);
	return (EXIT_SUCCESS);
}

static ssize_t		parse_tube(char *line, t_map *map, size_t *tubes)
{
	char 	**rooms;
	int		dash;
	int		i;
	
	dash = 0;
	i = 0;
	while (line[i])
	{
		i++;
		if (line[i] == '-')
			dash += 1;
	}
	if (dash != 1)
		return (parse_error(4));
	rooms = ft_strsplit(line, '-');
	if (!rooms)
		return (parse_error(5));
	if (add_tubes(map, rooms) == EXIT_FAILURE)
		return (parse_error(6));
	(*tubes)++;
	free_room_names(rooms);
	return (EXIT_SUCCESS);
}

ssize_t		parse_tubes(t_input_reader *input, t_map *map, size_t *i)
{
	size_t		tubes;

	tubes = 0;
	while (*i < input->num_lines)
	{
		if (is_comment(input->lines[*i]) == 0)
		{
			if (parse_tube(input->lines[*i], map, &tubes) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		(*i)++;
	}
	if (tubes == 0)
		return (parse_error(7));
	return (EXIT_SUCCESS);
}

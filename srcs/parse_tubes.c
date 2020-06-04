/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_tubes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 15:39:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/04 19:12:42 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

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

static ssize_t		add_tubes(t_map *map, char **rooms)
{
	t_room *room1;
	t_room *room2;

	room1 = (t_room *)search_ht(map->rooms, rooms[0]);
	room2 = (t_room *)search_ht(map->rooms, rooms[1]);
	if (room1 == NULL || room2 == NULL)
		return (EXIT_FAILURE);
	if (add_neighbour(room1, room2) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (add_neighbour(room2, room1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	set_spe_sps(map, room1, room2);
	return (EXIT_SUCCESS);
}

static ssize_t		parse_tube(char *line, t_map *map, int *tubes)
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
	return (EXIT_SUCCESS);
}

ssize_t		parse_tubes(t_input_reader *input, t_map *map, size_t *i)
{
	int	tubes;

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

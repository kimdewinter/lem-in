/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_tubes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 15:39:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/08 15:41:46 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static ssize_t		add_tube(t_room *room, char *key)
{
	return (add_neighbour(room, key));
}

static ssize_t		add_tubes(t_map *map, char **rooms)
{
	t_room *room1;
	t_room *room2;

	room1 = (t_room *)search_ht(map->rooms, rooms[0]);
	room2 = (t_room *)search_ht(map->rooms, rooms[1]);
	if (room1 == NULL || room2 == NULL)
		return (EXIT_FAILURE);
	if (add_tube(room1, rooms[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (add_tube(room2, rooms[0]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
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
		return (ft_error("Invalid number of dashes in link line\n",
		EXIT_FAILURE));
	rooms = ft_strsplit(line, '-');
	if (!rooms)
		return (ft_error("Error allocating memory\n", EXIT_FAILURE));
	if (add_tubes(map, rooms) == EXIT_FAILURE)
		return (ft_error("Error adding link\n", EXIT_FAILURE));
	/* free rooms */
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
		return (ft_error("No links provided\n", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

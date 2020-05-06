/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_tubes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 15:39:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/06 16:55:37 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int		add_tube(t_room *room, char *key)
{
	if (!add_neighbour(room, key))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		add_tubes(t_map *map, char **rooms)
{
	t_room *room1;
	t_room *room2;

	room1 = (t_room *)search_ht(map->rooms, rooms[0]);
	room2 = (t_room *)search_ht(map->rooms, rooms[1]);
	if (room1 == NULL || room2 == NULL)
		return (EXIT_FAILURE);
	if (!add_tube(room1, rooms[1]))
		return (EXIT_FAILURE);
	if (!add_tube(room2, rooms[0]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		parse_tube(char *line, t_map *map, int *tubes)
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
		return (ft_error("Error allocating memory\n", 0));
	if (!add_tubes(map, rooms))
		return (ft_error("Error adding link\n", 0));
	/* free rooms */
	(*tubes)++;
	return (EXIT_SUCCESS);
}

int		parse_tubes(t_input_reader *input, t_map *map, size_t *i)
{
	int	tubes;

	tubes = 0;
	while (*i < input->num_lines)
	{
		if (!is_comment(input->lines[*i]))
		{
			if (!parse_tube(input->lines[*i], map, &tubes))
				return (EXIT_FAILURE);
		}
		(*i)++;
	}
	if (tubes == 0)
		return (ft_error("No links provided\n", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

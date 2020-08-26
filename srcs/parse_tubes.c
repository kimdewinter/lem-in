/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_tubes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 15:39:25 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/26 16:08:17 by lravier       ########   odam.nl         */
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

static int		add_tubes(t_room *room1, t_room *room2)
{
	if (check_duplicate_tube(room1, room2) == 1)
		return (15);
	if (add_neighbour(room1, room2) == EXIT_FAILURE)
		return (0);
	if (add_neighbour(room2, room1) == EXIT_FAILURE)
		return (0);
	return (1);
}

static t_room	*find_room_name(char *line, size_t *i, t_map *map)
{
	size_t	len;
	char	*tmp;
	t_room	*room;

	len = ft_strlen(line);
	tmp = NULL;
	room = NULL;
	while (*i <= len)
	{
		if (*i != 0)
			tmp = ft_strsub(line, 0, *i);
		if (tmp != NULL)
			room = search_ht(map->rooms, tmp);
		if (room != NULL)
		{
			free(tmp);
			return (room);
		}
		free(tmp);
		tmp = NULL;
		(*i)++;
	}
	return (room);
}

static size_t	parse_tube(char *line, t_map *map, size_t *tubes)
{
	t_room	*room1;
	t_room 	*room2;
	size_t	i;
	size_t	j;
	size_t	error;

	i = 0;
	j = 0;
	room1 = find_room_name(line, &i, map);
	if (room1 == NULL)
		return (0);
	if (line[i] != '-')
		return (0);
	else
		i++;
	room2 = find_room_name(&line[i], &j, map);
	if (room2 == NULL)
		return (0);
	if (line[i + j] != '\0')
		return (0);
	if (room1 == room2)
		return (0);
	error = add_tubes(room1, room2);
	if (error != 1)
		return (error);
	(*tubes)++;
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

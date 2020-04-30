/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 17:33:44 by kim           #+#    #+#                 */
/*   Updated: 2020/04/30 17:42:38 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static size_t	is_antmount(char *line)
{
	if (*line != '\0' && ft_isdigit(*line) == 1)
	{
		while (*line != '\0' && ft_isdigit(*line) == 1)
		{
			line++;
		}
		if (*line != '\0' && *line == '\n')
			return (1);
	}
	return (0);
}

static size_t	is_room(char *line)
{
	if (ft_isalnum(*line) == 1 && *line != ' ' && *line != '\n'
			&& *line != 'L' && *line != '#')
	{
		while (ft_isalnum(*line) == 1 && *line != ' ' && *line != '\n')
			line++;
		if (*line == ' ')
			line++;
		else
			return (0);
		while (ft_isdigit(*line) == 1 && *line != ' ')
			line++;
		if (*line == ' ')
			line++;
		else
			return (0);
		while (ft_isdigit(*line) == 1)
			line++;
		if (*line == '\n' || *line == '\0')
			return (1);
	}
	return (0);
}

static size_t	is_tube(char *line)
{
	int		i;
	char	**words;
	int		dash;

	/* Free words! */
	i = 0;
	dash = 0;
	while(line[i])
	{
		if (line[i] == '-')
			dash += 1;
		i++;
	}
	i = 0;
	if (dash != 1)
		return (0);
	words = ft_strsplit(line, '-');
	while (words[i] != NULL)
		i++;
	if (i != 2)
		return (0);
	if (ft_strcmp(words[0], words[1]) == 0)
		return (0);
	/* Check whether room name exists in collection of rooms */
	return (1);
}

static size_t	is_comment(char *line)
{
	if (*line == '#' && line[1] == '#')
		return (1);
	return (0);
}

ssize_t	parse_input(t_input_reader *input, t_map *map)
{
	size_t	i;

	i = 0;
	if (input != NULL && map != NULL)
	{
		while (i < input->num_lines && input->lines[i] != NULL)
		{
			if (is_tube(input->lines[i]) == 1)
				parse_tube(input, map, input->lines[i]);
			else if (is_room(input->lines[i]) == 1)
				parse_room(input, map, input->lines[i]);
			else if (is_comment(input->lines[i]) == 1)
			{
				// if (i + 1 < input->num_lines && input->lines[i + 1] != NULL
				// 	&& is_room(input->lines[i + 1]) == 1)
				// {
				// 	parse_comment(input, map, input->lines[i], input->lines[i + 1]);
				// }
				// TO BE FINISHED
			}
			else if (is_antmount(input->lines[i]) == 1)
				parse_(input, map, input->lines[i]);
			else
				return (EXIT_FAILURE);
			i++;
		}
		if (i == input->num_lines)
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
/*
ROUGH PSEUDO-CODE:
while (SOMETHING)
{
	if (line == tube)
		tube();
	else if (line == room)
		room();
	else if (line == comment)
		comment();
	else if (line == antmount)
		antmount();
	else
		return (EXIT_FAILURE);
	line++;
}
Check if room already exists
*/

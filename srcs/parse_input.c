/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 17:33:44 by kim           #+#    #+#                 */
/*   Updated: 2020/04/29 14:37:20 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

// PLACEHOLDER: FUNCTION THAT IDENTIFIES WHAT IS BEING GIVEN (room/tube/start/end)
/* if i = 0, then treat it as number of ants
	if line == command (start or end), set corresponding flag (or something)
	if comment: ignore
	if room: create room
	if link: implement link
	if empty line: error
*/

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
			line++;//stepping through room-name

		if (*line == ' ')
			line++;//step over the space
		else
			return (0);

		while (ft_isdigit(*line) == 1 && *line != ' ')
			line++;//step through x-coordinate

		if (*line == ' ')
			line++;//step over the space
		else
			return (0);
		
		while (ft_isdigit(*line) == 1)
			line++;//step through y-coordinate
		
		if (*line == '\n' || *line == '\0')
			return (1);//1 is only returned if a lot of conditions have been met
	}
	return (0);//default return is always 0; safer
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
	if (*line == '#' && line[1] != '#')
		return (1);
	return (0);
}

size_t	is_command(char *line)
{
	if (*line == '#' && line[1] == '#')
		return (1);
	return (0);
}

ssize_t	parse_input(char **input, t_map *map)
{
	find_start(input, map);
	find_end(input, map);
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
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 17:46:27 by kim           #+#    #+#                 */
/*   Updated: 2020/09/30 12:53:28 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

size_t			is_antmount(char *line)
{
	if (*line != '\0' && ft_isdigit(*line) == 1)
	{
		while (*line != '\0' && ft_isdigit(*line) == 1)
			line++;
		if (*line == '\0' || *line == '\n')
		{
			return (1);
		}
	}
	return (0);
}

static size_t	is_coordinate(char **line)
{
	if (!(ft_isdigit(**line) == 1 || **line == '-'))
		return (0);
	if (**line == '-')
	{
		(*line)++;
		if (ft_isdigit(**line) == 0)
			return (0);
	}
	while (ft_isdigit(**line) == 1 && **line != ' ')
		(*line)++;
	return (1);
}

size_t			is_room(char *line)
{
	if (*line >= '!' && *line <= '~' && *line != '#' && *line != 'L'
	&& *line != '-')
	{
		line++;
		while (*line >= '!' && *line <= '~' && *line != '-')
			line++;
		if (*line == ' ')
			line++;
		else
			return (0);
		if (is_coordinate(&line) == 0)
			return (0);
		if (*line == ' ')
			line++;
		else
			return (0);
		if (is_coordinate(&line) == 0)
			return (0);
		if (*line == '\n' || *line == '\0')
			return (1);
	}
	return (0);
}

static size_t	is_tube_check(char **words, int i)
{
	if (i != 2)
	{
		free_room_names(words);
		return (0);
	}
	if (ft_strcmp(words[0], words[1]) == 0)
	{
		free_room_names(words);
		return (0);
	}
	free_room_names(words);
	return (1);
}

size_t			is_tube(char *line)
{
	int		i;
	char	**words;
	int		dash;

	i = 0;
	dash = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			return (0);
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
	return (is_tube_check(words, i));
}

size_t			is_comment(char *line)
{
	if (ft_strcmp(line, "##end") == 0)
		return (3);
	else if (ft_strcmp(line, "##start") == 0)
		return (2);
	else if (*line == '#')
		return (1);
	return (0);
}
/*
** returns:
** 0 for not a comment
** 1 for regular comment
** 2 for start comment
** 3 for end comment
*/

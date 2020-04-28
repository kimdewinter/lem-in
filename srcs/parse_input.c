/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 17:33:44 by kim           #+#    #+#                 */
/*   Updated: 2020/04/28 18:44:48 by kim           ########   odam.nl         */
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
	if (ft_isalnum(*line) == 1 && *line != ' ')//does ft_isalnum return 0 when faced with a '\0'?
	{
		line++;
		while (ft_isalnum(*line == 1))
		{
			line++;
			if (*line == ' ')
			{
				line++;
				break;
			}
		}
		while (ft_isdigit(*line == 1))
		{
			line++;
			if (*line == ' ')
			{
				line++;
				break;
			}
		}
		while (ft_isdigit(*line == 1))
		{
			line++;
			if (*line == '\n')
			{
				line++;
				return (1);
			}
		}
	}
	return (0);
}//I'll improve this tomorrow

static size_t	is_tube(char *line)
{

}//LAURE: if you're bored, can you make an is_tube? returns 1 if its a tube, 0 if not

static size_t	is_comment(char *line)
{
	if (*line == '#' && line[1] != '#')
		return (1);
	return (0);
}

static size_t	is_command(char *line)
{
	if (*line == '#' && line[1] == '#')
		return (1);
	return (0);
}

ssize_t	parse_input(char **input, t_map *map)
{
/*
ROUGH PSEUDO-CODE:

IF (IS_ANTMOUNT(*input[i]))
{
	GOOD SHIT!
}
ELSE
	OH NOES!

WHILE (IS_ROOM(*input[i]))
{
	MAKE SOME ROOM!
}

WHILE (IS_TUBE(*input[i]))
{
	TUBIN' IT UP!
}
*/
}

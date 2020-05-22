/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 17:46:27 by kim           #+#    #+#                 */
/*   Updated: 2020/05/21 13:26:23 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

size_t	is_antmount(char *line)
{
	printf("%s\n", line);
	if (*line != '\0' && ft_isdigit(*line) == 1)
	{
		while (*line != '\0' && ft_isdigit(*line) == 1)
			line++;
		printf("%d %d %d\n", *line, '\0', '\n');
		/* Does GNL return including linebreak? */
		if (*line == '\0' || *line == '\n')
		{
			printf("Is antmount\n");
			return (1);
		}
	}
	return (0);
}

size_t	is_room(char *line)
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

size_t	is_tube(char *line)
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
	/* None of this checks for spaces! */
	if (ft_strcmp(words[0], words[1]) == 0)
		return (0);
	/* Check whether room name exists in collection of rooms */
	return (1);
}

size_t	is_comment(char *line)
{
	if (ft_strcmp(line, "##end") == 0)
		return (3);
	else if (ft_strcmp(line, "##start") == 0)
		return (2);
	else if (*line == '#')
		return (1);
	return (0);
}
/* returns:
** 0 for not a comment
** 1 for regular comment
** 2 for start comment
** 3 for end comment
*/

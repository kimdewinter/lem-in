/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 14:44:18 by lravier       #+#    #+#                 */
/*   Updated: 2020/04/29 13:29:21 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static int			copy_input(char **input)
{
	int		read;
	char	**input;
	int		i;
	char	*line;

/* how many lines? Make sure ends with NULL*/
	input = (char **)malloc(sizeof(char **) * 10);
	if (!input)
		return (ft_error("Error allocating memory\n", 0));
	read = 1;
	i = 0;
	line = 0;
	while (read > 0)
	{
		read = get_next_line(0, &line);
		input[i] = ft_strdup(line);
		if (line)
			free(line);
		i++;
	}
	if (read < 0)
		return (ft_error("Error reading input\n", 0));
	return (1);
}

int				read_input(t_map *map, char **input)
{
	if (!copy_input(input))
		return (0);
	parse_input(input, map);
}


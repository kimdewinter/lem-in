/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 14:44:18 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/06 15:14:06 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static t_input_reader	*resize_buffer(t_input_reader *input)
{
	t_input_reader	*new_buff;
	int				i;

	i = 0;
	new_buff->size = input->size * 2;
	new_buff->num_lines = input->num_lines;
	new_buff->lines = (char **)malloc(sizeof(char *) * new_buff->size);
	if (!new_buff->lines)
		return (NULL);
	while (i <= input->num_lines)
	{
		new_buff->lines[i] = input->lines[i];
		i++;
	}
	free (input->lines);
	input->lines = NULL;
	return (new_buff);
}

static int			copy_input(t_input_reader *input)
{
	int				read;
	int				i;
	char			*line;

/* how many lines? Make sure ends with NULL */
	read = 1;
	line = NULL;
	while (read > 0)
	{
		if (input->num_lines == (input->size - 1))
		{
			input = resize_buffer(input);
			if (!input)
				return (ft_error("Error allocating memory\n", EXIT_FAILURE));
		}
		read = get_next_line(STDIN_FILENO, &line);
		/* check whether line && reading success */
		if (read < 0)
			return (ft_error("Error reading input\n", 0));
		input->lines[input->num_lines] = ft_strdup(line);
		input->num_lines++;
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	if (read < 0)
		return (ft_error("Error reading input\n", EXIT_FAILURE));
	return (1);
}

static int		setup_input(t_input_reader *input)
{
	input->lines = (char **)malloc(sizeof(char *) * LINE_BUFF_SIZE);
	if (!input->lines)
		return (ft_error("Error allocating memory\n", EXIT_FAILURE));
	input->num_lines = 0;
	input->size = LINE_BUFF_SIZE;
}

int				read_input(t_map *map, t_input_reader *input)
{
	setup_input(input);
	if (!copy_input(input))
		return (0);
}


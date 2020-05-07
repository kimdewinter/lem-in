/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 14:44:18 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/07 14:59:07 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static ssize_t	resize_buffer(t_input_reader *input)
{
	char			**new_lines;
	size_t			i;

	i = 0;
	input->size = input->size * 2;
	new_lines = (char **)malloc(sizeof(char *) * input->size);
	if (!new_lines)
		return (EXIT_FAILURE);
	while (i < input->num_lines)
	{
		new_lines[i] = input->lines[i];
		i++;
	}
	free (input->lines);
	input->lines = new_lines;
	return (EXIT_SUCCESS);
}

static ssize_t		copy_input(t_input_reader *input)
{
	int				read;
	char			*line;

/* how many lines? Make sure ends with NULL */
	read = 1;
	line = NULL;
	while (read > 0)
	{
		if (input->num_lines == (input->size - 1))
		{
			if (resize_buffer(input) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		read = get_next_line(STDIN_FILENO, &line);
		/* check whether line && reading success */
		if (read < 0)
			return (ft_error("Error reading input\n", EXIT_FAILURE));
		input->lines[input->num_lines] = ft_strdup(line);
		input->num_lines++;
		if (line)
			free(line);
	}
	if (read < 0)
		return (ft_error("Error reading input\n", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

static ssize_t	setup_input(t_input_reader *input)
{
	input->lines = (char **)malloc(sizeof(char *) * LINE_BUFF_SIZE);
	if (!input->lines)
		return (ft_error("Error allocating memory\n", EXIT_FAILURE));
	input->num_lines = 0;
	input->size = LINE_BUFF_SIZE;
	return (EXIT_SUCCESS);
}

ssize_t			read_input(t_input_reader *input)
{
	setup_input(input);
	if (!copy_input(input))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

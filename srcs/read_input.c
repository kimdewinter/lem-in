/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 14:44:18 by lravier       #+#    #+#                 */
/*   Updated: 2020/08/25 16:25:00 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static ssize_t	resize_buffer(t_input_reader *input)
{
	char		**new_lines;
	size_t		i;

	i = 0;
	input->size = input->size * 2;
	new_lines = (char **)malloc(sizeof(char *) * input->size);
	if (!new_lines)
	{
		delete_input(input);
		return (EXIT_FAILURE);
	}
	while (i < input->size)
	{
		new_lines[i] = NULL;
		i++;
	}
	i = 0;
	while (i < input->num_lines)
	{
		new_lines[i] = input->lines[i];
		i++;
	}
	free(input->lines);
	input->lines = new_lines;
	return (EXIT_SUCCESS);
}

static ssize_t	copy_input(t_input_reader *input)
{
	int		read;

	read = 1;
	while (read > 0)
	{
		if (input->num_lines == input->size - 1)
		{
			if (resize_buffer(input) == EXIT_FAILURE)
				return (4);
		}
		read = get_next_line(STDIN_FILENO, &input->lines[input->num_lines]);
		if (read < 0)
			return (3);
		if (read > 0)
			input->num_lines++;
	}
	if (read < 0)
		return (3);
	return (1);
}

static ssize_t	setup_input(t_input_reader *input)
{
	size_t	i;

	i = 0;
	input->lines = (char **)malloc(sizeof(char *) * LINE_BUFF_SIZE);
	input->size = LINE_BUFF_SIZE;
	if (input->lines == NULL)
		return (ft_error("Error allocating memory\n", EXIT_FAILURE));
	while (i < input->size)
	{
		input->lines[i] = NULL;
		i++;
	}
	input->num_lines = 0;
	return (EXIT_SUCCESS);
}

ssize_t			read_input(t_input_reader *input)
{
	ssize_t		ret;

	if (setup_input(input) == EXIT_FAILURE)
		return (main_error(2));
	ret = copy_input(input);
	if (ret != 1)
		return (main_error(ret));
	return (EXIT_SUCCESS);
}

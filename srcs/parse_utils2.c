/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 17:46:27 by kim           #+#    #+#                 */
/*   Updated: 2020/09/30 16:59:56 by simoncleerd   ########   odam.nl         */
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

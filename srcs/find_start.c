/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_start.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 13:26:21 by lravier       #+#    #+#                 */
/*   Updated: 2020/04/29 13:42:45 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

static int		is_start(char *s)
{
	if (ft_strcmp(&s[2], "start") == 0)
		return (1);
	return (0);
}

int		find_start(char **input, t_map *map)
{
	int i;

	i = 0;
	while (input[i] != NULL)
	{
		if (is_command(input[i]))
		{
			if (is_start(input[i]))
			{
				if (is_room(input[i + 1]))
				{
					if (setup_room(&map->start))
						return (EXIT_SUCCESS);
					return (EXIT_FAILURE);
				}
				else
					return (EXIT_FAILURE);
			}
		}
		i++;
	}
	return (EXIT_FAILURE);
}
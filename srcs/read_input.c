/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 14:44:18 by lravier       #+#    #+#                 */
/*   Updated: 2020/04/28 16:09:38 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

/* if we get here line != null */
/* return 2 if next room is start, return 3 if next room is end? */
// static void	handle_line(const char *line, t_room **rooms, int i,
// t_map **map, int flags[])
// {
// 	/* is number of ants) */
// 	if (i == 0)
// 	{
// 		if (!handle_n_ants(line, map))
// 			return (0);
// 	}
// 	if (line[0] == '#')
// 	{
// 		if (!handle_hash(line, map, flags))
// 			return (0);
// 	}
// }

/* if i = 0, then treat it as number of ants
	if line == command (start or end), set corresponding flag (or something)
	if comment: ignore
	if room: create room
	if link: implement link
	if empty line: error
*/

int			read_input(t_map *map)
{
	char	*line;
	// int		num_ants;
	int		i;
	// int		flags[2];
	char	**input;
	map = NULL;
	int res = 1;

	i = 0;
	line = NULL;
	input = (char **)malloc(sizeof(char **) * 10);
	printf(" hello");
	while (res)
	{
		res = get_next_line(1, &line);
		printf("res %d", res);
		if (line)
		{
			// handle_line(line, rooms, i, map, flags);//zoiets
			input[i] = ft_strdup(line);
			free(line);
		}
		i++;
	}
	i = 0;
	while (i < 3)
	{
		printf("%s\n", input[i]);
		i++;
	}
	return (1);
}

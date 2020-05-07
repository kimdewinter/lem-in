/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem-in.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 11:18:06 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/07 15:08:04 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include <limits.h>
# include "../lib/lib.h"
# define LINE_BUFF_SIZE 10000

typedef struct	s_map
{
	ssize_t	antmount;//amount of ants
	char	*start;
	char	*end;
	t_table	*rooms;
	void	*routes;//type to be determined
}				t_map;

typedef struct	s_input_reader
{
	size_t	size;
	char	**lines;
	size_t	num_lines;
}				t_input_reader;


ssize_t	read_input(t_input_reader *input);
int		get_next_line(const int fd, char **line);
ssize_t	parse_input(t_map *map, t_input_reader *input);
ssize_t	parse_antmount(t_input_reader *input, t_map *map, size_t *i);
ssize_t	parse_rooms(t_input_reader *input, t_map *map, size_t *i);
ssize_t	parse_tubes(t_input_reader *input, t_map *map, size_t *i);
ssize_t	setup_room(t_room **dest,
					const char *name,
					const ssize_t xpos,
					const ssize_t ypos);
ssize_t	add_neighbour(t_room *room, const char *neighbour);
ssize_t	purge_room(t_room **room);
ssize_t	link_rooms(t_room *alpha, t_room *omega);
size_t	is_command(char *line);
size_t	is_comment(char *line);
size_t	is_tube(char *line);
size_t	is_room(char *line);
size_t	is_antmount(char *line);
unsigned long long		ft_atoi_ll(char *line, size_t *overflow);
#endif

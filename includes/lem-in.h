/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem-in.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 11:18:06 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/06 13:35:53 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include <limits.h>
# include "../lib/lib.h"
# define LINE_BUFF_SIZE 10000

typedef struct	s_room
{
	char			*name;
	ssize_t			xpos;
	ssize_t			ypos;
	size_t			neighbours_len;
	char			**neighbours;
	ssize_t	ant;//-1 means room is empty
}				t_room;

typedef struct	s_map
{
	size_t	antmount;//amount of ants
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


int		read_input(t_map *map, t_input_reader *input);
int		get_next_line(const int fd, char **line);
int		parse_antmount(char *line, t_map *map);
char	*ft_strdup(const char *s1);
ssize_t	setup_room(t_room **dest,
					const char *name,
					const ssize_t xpos,
					const ssize_t ypos);
ssize_t	add_neighbour(t_room *room, const char *neighbour);
ssize_t	purge_room(t_room **room);
ssize_t	link_rooms(t_room *alpha, t_room *omega);
size_t	is_command(char *line);
// t_entry *new_entry(char *key, char *value);
// ssize_t	insert_ht(t_table *table, char *key, void *value);
// void	*search_ht(t_table *table, char *key);
// ssize_t	delete_ht(t_table *table);

#endif

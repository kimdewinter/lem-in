/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem-in.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 11:18:06 by lravier       #+#    #+#                 */
/*   Updated: 2020/04/30 13:31:43 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "../libftprintf/includes/libftprintf.h"
# include "../libftprintf/libft/libft.h"
# include "../libftprintf/libft/get_next_line.h"
# include <limits.h>

typedef struct	s_room
{
	char			*name;
	ssize_t			xpos;
	ssize_t			ypos;
	size_t			links_len;
	char			**links;
	ssize_t	ant;//-1 means room is empty
}				t_room;


typedef struct	s_map
{
	size_t	antmount;//amount of ants
	t_room	*start;
	t_room	*end;
	void	*routes;//type to be determined
}				t_map;

int		read_input(t_map *map, char **input);
int		get_next_line(const int fd, char **line);
int		parse_antmount(char *line, t_map *map);
char	*ft_strdup(const char *s1);
ssize_t	setup_room(t_room **dest,
					const char *name,
					const ssize_t xpos,
					const ssize_t ypos,
					const size_t links);
ssize_t	purge_room(t_room **room);
ssize_t	link_rooms(t_room *alpha, t_room *omega);
size_t	is_command(char *line);

#endif

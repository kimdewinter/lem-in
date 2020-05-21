/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem-in.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 11:18:06 by lravier       #+#    #+#                 */
/*   Updated: 2020/05/21 16:19:29 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# define LINE_BUFF_SIZE 10000
# define INIT_ROUTE_PERC 25
# define ROUTE_LEN_INCR_MULT 2
# define BITFIELD_TYPE uint64_t
# define BITFIELD_SIZE 64
# include "../lib/lib.h"
# include <limits.h>
# include <stdint.h>

struct s_route;

typedef struct		s_room
{
	char			*name;
	ssize_t			xpos;//might become depecrated
	ssize_t			ypos;//might become depecrated
	size_t			ant;//might become depecrated
	struct s_room	**neighbours;
	size_t			neighbours_len;
	struct s_route	**routes;//array of t_routes that lead to the exit
	size_t			routes_len;
	size_t			*this_i;//array of the current t_room's index-position in each of the t_routes
	uint64_t		*bitroom;//TO DO: make this initialize to NULL
	size_t			room_i;//TO DO: make this initialize to the order in which the rooms were input
}					t_room;

typedef struct		s_route
{
	struct s_room	**route;
	size_t			len;
	uint64_t		*bitroute;
}					t_route;

typedef struct		s_map
{
	ssize_t			antmount;
	t_room			*start;
	t_room			*end;
	struct s_table	*rooms;
	void			*routes;//type to be determined
	size_t			bitfield_len;//TO DO: make this initialize (rooms_amount / BITFIELD_SIZE + 1)
}					t_map;

typedef struct	s_input_reader
{
	size_t			size;
	char			**lines;
	size_t			num_lines;
}					t_input_reader;

ssize_t				read_input(t_input_reader *input);
int					get_next_line(const int fd, char **line);
ssize_t				parse_input(t_map *map, t_input_reader *input);
ssize_t				parse_antmount(t_input_reader *input, t_map *map,
						size_t *i);
ssize_t				parse_rooms(t_input_reader *input, t_map *map, size_t *i);
ssize_t				parse_tubes(t_input_reader *input, t_map *map, size_t *i);
ssize_t				setup_room(t_room **dest,
						const char *name,
						const ssize_t xpos,
						const ssize_t ypos);
ssize_t				add_neighbour(struct s_table *table, t_room *room, char *neighbour);
ssize_t				purge_room(t_room **room);
ssize_t				link_rooms(t_room *alpha, t_room *omega);
size_t				is_command(char *line);
size_t				is_comment(char *line);
size_t				is_tube(char *line);
size_t				is_room(char *line);
size_t				is_antmount(char *line);
unsigned long long	ft_atoi_ll(char *line, size_t *overflow);
ssize_t				route_new(t_map *map);

// BITFIELD-TOOLKIT:
ssize_t				bite_room_new(t_room *room, const t_map *map);//takes a room and stores it's bitfield-form in room->bitroom
inline void			bite_route_add_room(t_route *route, const t_room *room);//takes a bitfield-form route and flips on a room's bit in it(WARNING: no success/failure return)
ssize_t				bite_route_new(t_route *route, const t_map *map);//takes the route->route array and stores it in bitfield-form in route->bitroute

//the following are merely functions for debugging:
void	debug(t_map *map);

#endif

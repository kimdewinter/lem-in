/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem-in.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 11:18:06 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/02 14:21:42 by kim           ########   odam.nl         */
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
	// struct s_route	**routes;//array of t_routes that lead to the exit
	// size_t			routes_len;
	size_t			*this_i;//deprecated ? array of the current t_room's index-position in each of the t_routes
	uint64_t		*bitroom;
	size_t			room_i;
}					t_room;

typedef struct		s_route
{
	int				solved;
	int				dead;
	struct s_room	**route;
	size_t			size;
	size_t			len;
	uint64_t		*bitroute;
}					t_route;

typedef struct		s_poscom
{
	struct s_route	**routes;
	size_t			num_routes;
	BITFIELD_TYPE	*bitroutes;
	size_t			i;//this is where in map->routes it is, it only ever moves forward
}					t_poscom;

typedef struct		s_combi
{
	struct s_route	**routes;
	BITFIELD_TYPE	*bitroutes;
	size_t			num_routes;
	size_t			turns;
}					t_combi;

typedef struct		s_map
{
	ssize_t			antmount;
	t_room			*start;
	t_room			*end;
	struct s_table	*rooms;
	struct s_route	**routes;
	size_t			num_routes;
	size_t			active_routes;
	size_t			bitfield_len;
	struct s_combi	**valid_combis;
	size_t			valid_combis_len;
	size_t			valid_combis_last_i;
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
						const ssize_t ypos, 
						size_t *num_room);
ssize_t				add_neighbour(struct s_table *table, t_room *room, char *neighbour);
ssize_t				purge_room(t_room **room);
ssize_t				link_rooms(t_room *alpha, t_room *omega);
size_t				is_command(char *line);
size_t				is_comment(char *line);
size_t				is_tube(char *line);
size_t				is_room(char *line);
size_t				is_antmount(char *line);
unsigned long long	ft_atoi_ll(char *line, size_t *overflow);
size_t				find_routes(t_map *);
size_t				init_routes(t_map *map);
size_t				add_to_route(t_route **curr_route, t_room *room, t_map *map);
size_t				add_route(t_map *map, t_route *route);
//the following are merely functions for debugging:
void				debug(t_map *map);
size_t				copy_route(t_route **src, t_route **dst, t_map *map);
t_route				*setup_route(size_t size);
void				print_routes(t_map *map);
ssize_t				route_new(t_map *map);
size_t				max_parallels(t_map *map);
ssize_t				parallelize(t_map *map);
ssize_t				combinatron(t_map *map,
						const t_poscom *parent,
						const size_t rtes_to_combi);
size_t				is_valid_combi(t_map *map,
						BITFIELD_TYPE *rte1,
						BITFIELD_TYPE *rte2);
ssize_t				copy_n_routes(t_route ***dst,
						t_route **src,
						const size_t n);

// BITFIELD-TOOLKIT:
ssize_t				bite_room_new(t_room *room, const t_map *map);//takes a room and stores it's bitfield-form in room->bitroom
// inline void			bite_route_add_room(t_route *route, const t_room *room);//takes a bitfield-form route and flips on a room's bit in it(WARNING: no success/failure return)
ssize_t				bite_route_convert(t_route *route, const t_map *map);//takes the route->route array and stores it in bitfield-form in route->bitroute
ssize_t				bite_route_copy(t_route *dst,
						const t_route *src,
						const t_map *map);//copies one t_route's bitfield-form route into another's
ssize_t				bite_alloc(BITFIELD_TYPE **dst, const t_map *map);
ssize_t				bite_alloc_noval(BITFIELD_TYPE **dst, const t_map *map);
ssize_t				bite_bitroute_bzero(BITFIELD_TYPE *bitroute, const t_map *map);
ssize_t				bite_bitroute_copy(BITFIELD_TYPE *dst,
						const BITFIELD_TYPE *src,
						const t_map *map);
ssize_t				bite_bitroute_merge(BITFIELD_TYPE *dst,
						const BITFIELD_TYPE *src1,
						const BITFIELD_TYPE *src2,
						const t_map *map);

//the following are merely functions for debugging:
void				debug(t_map *map);
ssize_t				calc_combinations(const size_t n, size_t r);
void	print_bitroute(t_map *map);
void	print_bitroom(t_map *map, t_room *room);
#endif

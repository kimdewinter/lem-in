/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lem-in.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 11:18:06 by lravier       #+#    #+#                 */
/*   Updated: 2020/06/09 10:53:10 by lravier       ########   odam.nl         */
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

struct s_room;

typedef struct	s_subpath
{
	size_t				len;
	struct s_room		*conj;
	struct s_room		**path;
	BITFIELD_TYPE		*bitconj;
}				t_subpath;

typedef	struct	s_route
{
	struct s_room	*last_conj;
	int				end;
	size_t			len;
	size_t			ants;
	struct s_room	**route;
	BITFIELD_TYPE	*bitroute;
}				t_route;

typedef struct	s_routes_wrapper
{
	size_t			size;
	size_t			num_paths;
	struct s_route	**routes;
}				t_routes_wrapper;

typedef struct		s_room
{
	int				sps;
	int				spe;
	char			*name;
	ssize_t			xpos;//might become depecrated
	ssize_t			ypos;//might become depecrated
	size_t			ant;//might become depecrated
	struct s_room	**neighbours;
	size_t			neighbours_len;
	size_t			room_i;
	size_t			num_options;
	size_t			routes_size;
	t_subpath		**routes;
	/* has routes to these conjunctions */
	BITFIELD_TYPE	*bitconj;
}					t_room;

typedef struct	s_queue
{
	int					new_conj;
	struct s_subpath	*path;
	struct s_room		*dst;
	struct s_room		*src;
}				t_queue;

typedef struct	s_qwrap
{
	t_list			**queue;
	t_list			*last;
}				t_qwrap;

typedef struct		s_poscom
{
	struct s_route	**routes;
	size_t			num_routes;
	BITFIELD_TYPE	*bitroutes;
	size_t			i;//this is where in map->routes it is, it only ever moves forward
}					t_poscom;
/*
** poscom means "possible combination",
** it is recursively used by the parallelizer to find valid route combinations
*/

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
	size_t			bitfield_len;
	struct s_route	**best_combi;
	size_t			best_combi_used;
	size_t			best_combi_len;
	size_t			best_combi_turns;
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
size_t				sanitize_input(t_map *map);
ssize_t				parse_tubes(t_input_reader *input, t_map *map, size_t *i);
ssize_t				setup_room(t_room **dest,
						const char *name,
						const ssize_t xpos,
						const ssize_t ypos, 
						size_t *num_room);
ssize_t				add_neighbour(t_room *room, t_room *neighbour);
ssize_t				purge_room(t_room **room);
ssize_t				link_rooms(t_room *alpha, t_room *omega);
size_t				is_command(char *line);
size_t				is_comment(char *line);
size_t				is_tube(char *line);
size_t				is_room(char *line);
size_t				is_antmount(char *line);
unsigned long long	ft_atoi_ll(char *line, size_t *overflow);
void				free_room_names(char **rooms);

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
ssize_t				handle_err_para(size_t err_code, const char *line);
ssize_t				handle_err_comtron(size_t err_code, const char *line);
ssize_t				handle_err_biter(size_t err_code, const char *line);

// BITFIELD-TOOLKIT:
ssize_t				bite_alloc(BITFIELD_TYPE **dst, const t_map *map);
ssize_t				bite_alloc_noval(BITFIELD_TYPE **dst, const t_map *map);
// ssize_t				bite_bitroute_bzero(BITFIELD_TYPE *bitroute, const t_map *map);
ssize_t				bite_bitroute_copy(BITFIELD_TYPE *dst,
						const BITFIELD_TYPE *src,
						const t_map *map);
size_t				copy_bitconj(BITFIELD_TYPE **dst, BITFIELD_TYPE *src,
						t_map *map);
ssize_t				bite_bitroute_merge(BITFIELD_TYPE *dst,
						const BITFIELD_TYPE *src1,
						const BITFIELD_TYPE *src2,
						const t_map *map);
size_t				calc_cost(size_t ants, const t_poscom *routes);
ssize_t				calc_combinations(const size_t n, size_t r);
// Queue management
size_t				setup_queue(t_qwrap **queue, t_map *map);
size_t				adjust_queue(t_map *map, t_qwrap *queue, size_t len);
t_list				*new_queue_item(t_subpath *pt, t_room *dst, t_room *src);
void				ft_lstaddend_no_alloc(t_qwrap *lst, t_list *new);

// Route finding
size_t				find_routes(t_map *map);
size_t				setup_paths(t_map *map);
t_subpath			*new_subpath(t_room *conj);
t_room				**new_path(size_t size);
size_t				add_subpath(t_room *dst, t_subpath *pt);
size_t				add_new_conj_subpath(t_room *dst, t_room *src);
size_t				add_to_conj_path(t_room *dst, t_room *src,
					t_subpath *pt);
int					has_path_to_conj(t_room *curr, t_room *conj);
int					is_new_conj(t_room *src, t_room *curr, t_subpath *spt);

// Path building
size_t				setup_routes(t_routes_wrapper **rw, t_map *map);
size_t				setup_starting_paths(t_routes_wrapper *rw, t_map *map,
					size_t *active);
size_t				increase_routes_capacity(t_routes_wrapper *rw);
size_t				build_paths(t_map *map);
void				bite_route_add_conj(t_route *route, const t_room *conj);

//the following are merely functions for debugging:
void				debug(t_map *map);
void				print_bitroute(t_map *map);
void				print_bitroom(t_map *map, t_room *room);
void				print_queue(t_list **queue);
void				print_path(t_subpath *pt);
void				print_bitconj(BITFIELD_TYPE *arr, size_t len);
void				print_troute(t_routes_wrapper *wroutes);
void				print_solution(t_map *map);

size_t				parse_error(size_t err_code);
void				free_queue(t_qwrap **rw);
void				free_queue_item(t_list *curr);
void				print_route_rooms(const t_route *rte,
						const size_t *rte_index);
void				print_n_routes(const t_route **rtes, const size_t n);

void				calculate_ants_per_path(size_t ants, size_t *left_ants,
						t_poscom *best);
long double			calc_paths_avg(size_t num_paths, const t_poscom *routes);
long double			calc_ants_avg(size_t ants, size_t num_paths);
#endif

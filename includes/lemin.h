/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/23 19:24:52 by kim           #+#    #+#                 */
/*   Updated: 2020/07/17 16:57:01 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define LINE_BUFF_SIZE 10000
# define INIT_ROUTE_PERC 25
# define ROUTE_LEN_INCR_MULT 2
# define BITFIELD_TYPE uint64_t
# define BITFIELD_SIZE 64
# define COMVAULT_LEN_INIT 9
# define COMVAULT_LEN_INCR_MULT 10

# include "../lib/lib.h"
# include <limits.h>
# include <stdint.h>

struct s_room;
struct s_route;

typedef struct			s_routeput
{
	char				**rooms;
	size_t				rooms_len;
	size_t				*ants;
	size_t				ants_received;
	size_t				finished;
}						t_routeput;
/*
** used to output the execution of the solution to general output
*/

typedef struct			s_best
{
	struct s_route		**combi;
	size_t				used;
	size_t				len;
	size_t				turns;
}						t_best;
/*
** the combination of routes chosen as being the best one (so far)
*/

typedef struct			s_comvault
{
	size_t				coms_of_num;
	struct s_poscom		**coms;
	size_t				coms_len;
	size_t				coms_used;
}						t_comvault;
/*
** there will be a comvault of poscoms of 1, of poscoms of 2, etc
*/

typedef struct			s_poscom
{
	struct s_route		**routes;
	size_t				num_routes;
	BITFIELD_TYPE		*bitroutes;
	size_t				map_routes_i;
	size_t				turns;
}						t_poscom;
/*
** "poscom" means "possible combination",
** it is recursively used by the parallelizer to find valid route combinations
** "i" indexes where in map->routes it is, only ever moves forward
*/

typedef	struct			s_route
{
	struct s_room		**route;
	size_t				len;
	BITFIELD_TYPE		*bitroute;
	struct s_room		*last_conj;
	int					end;
	size_t				ants;
}						t_route;
/*
** the structure of each valid route from the start to the end room
*/

typedef struct			s_routes_wrapper
{
	size_t				size;
	size_t				num_paths;
	struct s_route		**routes;
}						t_routes_wrapper;

typedef struct			s_queue
{
	int					handled;
	int					new_conj;
	struct s_subpath	*path;
	struct s_room		*dst;
	struct s_room		*src;
	struct s_queue		*prev;
	struct s_queue		*next;
}						t_queue;

typedef struct			s_qwrap
{
	BITFIELD_TYPE		*in_queue;
	t_queue				**queue;
	t_queue				*last;
	size_t				items;
	size_t				round;
}						t_qwrap;

typedef struct			s_subpath
{
	int					added_this_turn;
	int					sp;
	ssize_t				start;
	size_t				size;
	size_t				segment_len;
	size_t				len;
	struct s_room		*conj;
	struct s_room		**path;
	struct s_subpath	*next;
	BITFIELD_TYPE		*bitconj;
}						t_subpath;

typedef struct			s_room
{
	int					sps;
	int					spe;
	char				*name;
	ssize_t				xpos;
	ssize_t				ypos;
	size_t				ant;
	size_t				viable_nbs;
	int					is_conj;
	int					checked;
	int					dead_end;
	struct s_room		**neighbours;
	size_t				weight;
	size_t				neighbours_len;
	size_t				room_i;
	size_t				num_options;
	t_subpath			**routes;
	size_t				routes_size;
	BITFIELD_TYPE		*bitconj;
}						t_room;
/*
** the structure of each room in the "ant hill"
*/

typedef struct			s_map
{
	ssize_t				antmount;
	t_room				*start;
	t_room				*end;
	struct s_table		*rooms;
	struct s_route		**routes;
	size_t				num_routes;
	size_t				bitfield_len;
	struct s_best		solution;
}						t_map;
/*
** the program's main struct
*/

typedef struct			s_input_reader
{
	size_t				size;
	char				**lines;
	size_t				num_lines;
}						t_input_reader;
/*
** standalone struct only used for reading and parsing input
*/

/*
** READER
*/
int						get_next_line(const int fd, char **line);
ssize_t					read_input(t_input_reader *input);

/*
** PARSER
*/
ssize_t					add_neighbour(t_room *room, t_room *neighbour);
unsigned long long		ft_atoi_ll(char *line, size_t *overflow);
void					free_room_names(char **rooms);
size_t					is_antmount(char *line);
size_t					is_command(char *line);
size_t					is_comment(char *line);
size_t					is_room(char *line);
size_t					is_tube(char *line);
ssize_t					link_rooms(t_room *alpha, t_room *omega);
ssize_t					parse_antmount(t_input_reader *input,
										t_map *map,
										size_t *i);
ssize_t					parse_input(t_map *map, t_input_reader *input);
ssize_t					parse_rooms(t_input_reader *input,
									t_map *map,
									size_t *i);
ssize_t					parse_tubes(t_input_reader *input,
									t_map *map,
									size_t *i);
ssize_t					purge_room(t_room **room);
ssize_t					sanitize_input(t_map *map);
ssize_t					setup_room(t_room **dest,
									const char *name,
									const ssize_t xpos,
									const ssize_t ypos,
									size_t *num_room);

/*
** ROUTE FINDING
*/
ssize_t					find_routes(t_map *map);
ssize_t					route_error(size_t err_code);
/*
** ROUTE FINDING CONFLICTS
*/
int						is_junction(t_room *src, t_room *dst, t_map *map);
/*
** ROUTE FINDING UTILS
*/
ssize_t					increase_route_size(t_subpath **pt, t_map *map);
ssize_t					increase_routes_size(t_room **dst, t_map *map);
ssize_t					add_path_to_room(t_queue *item,
											t_map *map,
											t_subpath **new);
ssize_t					add_to_path(t_subpath *pt, t_room *add, t_map *map);
t_room					**new_path(size_t size);
ssize_t					new_subpath(t_subpath **new, t_room *conj, t_map *map);
ssize_t					create_new_path(t_subpath **new,
											t_subpath *pt,
											t_room *conj,
											t_map *map);
/*
** QUEUE MANAGEMENT
*/
ssize_t					adjust_queue(t_qwrap *qr, t_map *map, size_t len);
/*
** QUEUE MANAGEMENT UTILS
*/
void					delete_path(t_subpath **pt);
t_queue					*new_queue_item(t_subpath *pt,
										t_room *dst,
										t_room *src);
void					add_item_queue(t_qwrap **qr, t_queue *new);
ssize_t					setup_queue(t_qwrap **qr, t_map *map);
ssize_t					add_to_queue(t_qwrap *qr,
										t_room *src,
										t_room *dst,
										t_subpath *pt);
void					remove_queue_item(t_qwrap *qr, t_queue *item);
/*
** QUEUE MANAGEMENT CHECKS
*/
int						check_length_spe(t_subpath *path,
											t_room *nb,
											t_map *map);
size_t					is_viable_for_path(t_map *map,
											t_queue *item,
											t_room *nb,
											t_subpath *path);
int						check_length(t_subpath *new_path, t_room *curr);
ssize_t					add_nb_to_queue(t_map *map,
										t_queue *item,
										t_room *nb,
										t_qwrap *qr);
/*
** BUILD_ROUTES
*/
ssize_t					assemble_all_routes(t_map *map);
/*
** PARALLELIZER
*/
ssize_t					calc_combinations(long long unsigned *result,
											const size_t n,
											size_t r);
size_t					calc_cost(size_t ants, const t_poscom *routes);
ssize_t					commit_best(const t_poscom *bestcom, t_best *new_entry);
ssize_t					expand_comvault(t_comvault *comvault);
ssize_t					handle_err_comtron(size_t err_code, const char *line);
ssize_t					handle_err_para(size_t err_code, const char *line);
ssize_t					max_parallels(size_t *result, const t_map *map);
ssize_t					parallelize(t_map *map);
ssize_t					parallelize_multiples_of(const t_comvault *previous,
													t_comvault *current,
													t_poscom **bestcom,
													const t_map *map);

/*
** BITFIELD-TOOLKIT
*/
void					add_to_bitfield(t_room *curr, uint64_t *bitfield);
ssize_t					bite_alloc(BITFIELD_TYPE **dst, const t_map *map);
ssize_t					bite_alloc_noval(BITFIELD_TYPE **dst, const t_map *map);
ssize_t					bite_bitroute_copy(BITFIELD_TYPE *dst,
											const BITFIELD_TYPE *src,
											const t_map *map);
ssize_t					bite_bitroute_merge(BITFIELD_TYPE **dst,
											const BITFIELD_TYPE *src1,
											const BITFIELD_TYPE *src2,
											const t_map *map);
void					bite_free(BITFIELD_TYPE **bitfield, const t_map *map);
ssize_t					copy_bitconj(BITFIELD_TYPE **dst,
										BITFIELD_TYPE *src,
										t_map *map);
ssize_t					handle_err_biter(size_t err_code, const char *line);
int						room_in_bitfield(t_room *curr, BITFIELD_TYPE *bitfield);

/*
** OUTPUTTER
*/
void					calculate_ants_per_path(size_t ants,
												const t_best *best);
void					execute_route(t_routeput *route, const size_t new_ant);
ssize_t					parse_error(size_t err_code);
ssize_t					output_result(const t_input_reader *input,
										const t_map *map);

/*
** CLEANER
*/
void					delete_all_comvaults(t_comvault **comvaults,
												const size_t len);
void					delete_all_routes(t_map *map);
void					delete_all_rooms(t_table *rooms);
void					delete_map(t_map *map);

/*
** DEBUGGING
*/
void					debug(t_map *map);
void					print_bitroom(t_map *map, t_room *room);
void					print_bitroute(t_map *map);
void					print_bitconj(BITFIELD_TYPE *arr, size_t len);
void					print_n_routes(const t_route **rtes, const size_t n);
void					print_path(t_subpath *pt);
void					print_queue(t_qwrap *qr);
void					print_route_rooms(const t_route *rte,
											const size_t *rte_index);
void					print_routeput(t_routeput **routes, size_t len);
void					print_solution(t_map *map);
void					print_troute(t_routes_wrapper *wroutes);
void					print_paths(t_room *room);
void					print_routes(t_map *map);
#endif

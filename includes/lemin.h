/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/23 19:24:52 by kim           #+#    #+#                 */
/*   Updated: 2020/07/31 15:24:52 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define LINE_BUFF_SIZE 10000
# define INIT_ROUTE_PERC 25
# define ROUTES_LEN_INCR_MULT 2
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
	size_t				used;
	BITFIELD_TYPE		*bitroute;
	size_t				ants;
}						t_route;
/*
** the structure of each valid route from the start to the end room
*/

typedef struct			s_bfs_route
{
	struct s_room		**route;
	size_t				len;
	size_t				used;
	struct s_room		*next_to_add;
}						t_bfs_route;

typedef struct			s_bfs_vault
{
	struct s_bfs_route	**routes;
	struct s_bfs_route	*shortest;
	size_t				len;
	size_t				used;
	size_t				next_rnd_used;
	BITFIELD_TYPE		*visited;
}						t_bfs_vault;

typedef struct			s_room
{
	char				*name;
	ssize_t				xpos;
	ssize_t				ypos;
	size_t				ant;
	int					dead_end;
	struct s_room		**neighbours;
	struct s_tube		*tubes;
	size_t				neighbours_len;
	size_t				room_i;
	BITFIELD_TYPE		*bitroom;
}						t_room;
/*
** the structure of each room in the "ant hill"
*/

typedef struct			s_tube
{
	ssize_t				posval;
	ssize_t				poscap;
	ssize_t				negval;
	ssize_t				negcap;
}						t_tube;

typedef struct			s_map
{
	ssize_t				antmount;
	t_room				*start;
	t_room				*end;
	struct s_table		*rooms;
	struct s_route		**routes;
	size_t				routes_len;
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
ssize_t					branch_bfs_route(const t_bfs_route *parent,
											t_bfs_vault *vault,
											t_room *next_to_add,
											const t_map *map);
ssize_t					allocinit_singleroom_route(t_route **dst,
													t_room *first_room,
													const t_map *map);
ssize_t					allocopy_route(t_route **dst,
										const t_route *src,
										t_room *room_to_add,
										const t_map *map);
ssize_t					find_routes(t_map *map);
ssize_t					handle_err_route_finder(size_t err_code,
												const char *line);
/*
** BFS UTILS
*/
t_room      			**create_new_route(size_t size);
ssize_t					add_bfs_room(t_bfs_route *bfs_route, t_room *to_add);
/*
** BFS RESIZE
*/
ssize_t					increase_route_size(t_bfs_route *bfs_route);
ssize_t					increase_vault_size(t_bfs_vault *vault, const t_map *map);
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
ssize_t					bite_add_room_to_bitfield(BITFIELD_TYPE *dst,
													const BITFIELD_TYPE *src,
													const t_map *map);
ssize_t					bite_biteroute_allocmerge(BITFIELD_TYPE **dst,
											const BITFIELD_TYPE *src1,
											const BITFIELD_TYPE *src2,
											const t_map *map);
void					bite_free(BITFIELD_TYPE **bitfield, const t_map *map);
ssize_t					allocopy_bitfield(BITFIELD_TYPE **dst,
											BITFIELD_TYPE *src,
											t_map *map);
ssize_t					handle_err_biter(size_t err_code, const char *line);
int						room_in_bitfield(t_room *curr, BITFIELD_TYPE *bitfield);
ssize_t					bite_room_new(t_room *room, const t_map *map);

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

#endif

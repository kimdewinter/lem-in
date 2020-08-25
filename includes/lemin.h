/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/23 19:24:52 by kim           #+#    #+#                 */
/*   Updated: 2020/08/25 17:07:50 by kim           ########   odam.nl         */
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
# define LVL_GRPH_E2S 0
# define LVL_GRPH_S2E 1
# define EXIT_ROUTEFOUND 2
# define EXIT_NO_BLOCKS 2
# define DEBUG 0
# define PATHS_DONE 2

# include "../lib/lib.h"
# include <limits.h>
# include <stdint.h>

struct s_room;
struct s_route;

typedef struct			s_weight_wrap
{
	BITFIELD_TYPE		*visited;
	BITFIELD_TYPE		*in_paths;
	struct s_weight		**q;
}						t_weight_wrap;

typedef struct			s_weight
{
	size_t				dist;
	struct s_room		*dst;
	struct s_weight		*next;
}						t_weight;

typedef struct			s_conn_wrap
{
	size_t				items;
	struct s_connection	**q;
	BITFIELD_TYPE		*visited;
}						t_conn_wrap;

typedef	struct			s_connection
{
	int					add;
	struct s_room		*src;
	struct s_room		*src_nb;
	struct s_room		*dst_nb;
	struct s_room		*dst;
	size_t				dist;
	struct s_connection	*next;
	struct s_connection	*prev;
}						t_connection;

typedef struct			s_dupl
{
	struct s_connection	curr;
	struct s_connection	other;
	ssize_t				i;
	ssize_t				j;
}						t_dupl;

typedef struct			s_triangle
{
	struct s_connection	*src_side;
	struct s_connection	nb_src;
	struct s_connection	side_nb;
}						t_triangle;

typedef	struct			s_diamond
{
	int					common_dst_found;
	size_t				nb_improved_by_side;
	size_t				side_improved_by_nb;
	struct s_connection	*src_side;
	struct s_connection	*nb_src;
	struct s_connection	*side_nb;
	struct s_connection	side_dst;
	struct s_connection	nb_dst;
	struct s_room		*curr_nb_nb;
	struct s_room		*curr_nb_side;
}						t_diamond;

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
	BITFIELD_TYPE		*in_paths;
	size_t				used;
	size_t				len;
	size_t				prev_turns;
	size_t				turns;
}						t_best;
/*
** the combination of routes chosen as being the best one (so far)
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

typedef struct			s_room
{
	char				*name;
	int					spe;
	int					sps;
	int					is_junction;
	size_t				ant;
	struct s_room		**neighbours;
	size_t				neighbours_len;
	size_t				room_i;
	BITFIELD_TYPE		*bitroom;
	ssize_t				dist_to_end;
	ssize_t				dist_to_start;
	size_t				spe_len;
	struct s_room		*spe_start;
	size_t				sps_len;
	struct s_room		*sps_start;
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
** PARSER
*/
ssize_t					main_error(size_t err_code);
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
ssize_t					add_room(const char *line, t_map *map,
									size_t *num_room);
ssize_t					add_special_room(t_input_reader *input,
									t_map *map,
									size_t *i,
									size_t *num_room);
ssize_t					check_duplicate_room(const char *room_name,
												const t_map *map);
ssize_t					parse_tubes(t_input_reader *input,
									t_map *map,
									size_t *i);
ssize_t					sanitize_input(t_map *map);
ssize_t					set_spe_rooms(t_map *map);
ssize_t					set_sps_rooms(t_map *map);
ssize_t					setup_room(t_room **dest,
									const char *name,
									size_t *num_room);
/*
** UNNECESSARY TUBES OPTION CHECKS
*/
int						is_junction(t_room *curr, t_map *map);

/*
** UNNECESSARY TUBES UTILS
*/
void					del_tube(t_room *from, t_room *to, t_map *map);
/*
** ROUTE FINDING
*/
size_t					calc_cost_add_route(const t_best *candidate,
											t_route *route,
											t_map *map);
void					reset_dists(t_table *rooms, int to_start, int to_end);
void					compare_candidate_best(t_map *map, t_best *candidate);
ssize_t					remove_blockage(t_best *candidate, t_map *map);
ssize_t					remove_conn(t_best *candidate,
									t_room *block,
									t_map *map);
ssize_t					find_parallel_routes(t_best *candidate, t_map *map);
void					find_best_option(t_room *start,
											BITFIELD_TYPE *visited,
											ssize_t *i);
ssize_t					set_weights(t_map *map,
									int flow,
									BITFIELD_TYPE *in_paths);
ssize_t					add_q_item(t_weight **q, size_t round, t_room *dst);
void					remove_q_item(t_weight **q);
ssize_t					create_q(t_weight_wrap **qr, BITFIELD_TYPE *in_paths,
t_map *map);
size_t					calc_cost(size_t ants, const t_best *routes);
size_t					ft_round_rest(long double rest);
ssize_t					find_routes(t_map *map);
ssize_t					find_routes_df(t_best *candidate, const t_map *map);
/*
** ROUTE FINDING UTILS
*/
void					set_route(t_best *candidate,
									t_route *route,
									t_map *map);
ssize_t					init_route(t_best *candidate,
									t_map *map,
									t_route *route);
ssize_t					init_combi(t_map *map, t_best **candidate);
void					reset_route(t_route *route);
ssize_t					setup_route(t_route *route, t_map *map);
int						is_improvement(t_best *best, t_route *add, t_map *map);
void					setup_candidate(t_best *candidate);
ssize_t					free_find_parallel(BITFIELD_TYPE **visited,
											t_route *route,
											ssize_t	ret);

ssize_t					setup_routefinder(BITFIELD_TYPE **visited,
											t_route *route,
											t_map *map);
/*
** BITFIELD-TOOLKIT
*/
void					merge_bitfield(BITFIELD_TYPE *dst,
										BITFIELD_TYPE *src,
										t_map *map);
void					bite_add_room_to_bitfield(t_room *curr,
													uint64_t *bitfield);
ssize_t					bite_alloc(BITFIELD_TYPE **dst, const t_map *map);
ssize_t					bite_alloc_noval(BITFIELD_TYPE **dst, const t_map *map);
ssize_t					bite_bitroute_copy(BITFIELD_TYPE *dst,
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
int						room_in_bitfield(const t_room *curr,
											BITFIELD_TYPE *bitfield);
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
ssize_t					setup_all_routeputs(t_routeput ***routes,
											const t_map *map);

/*
** CLEANER
*/
void					delete_input(t_input_reader *input);
void					delete_all_routes(t_map *map);
void					delete_all_rooms(t_table *rooms);
void					delete_map(t_map *map);
void					delete_solution(t_best *solution);

#endif

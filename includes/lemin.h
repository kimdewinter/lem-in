/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/23 19:24:52 by kim           #+#    #+#                 */
/*   Updated: 2020/08/17 14:11:15 by kim           ########   odam.nl         */
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

# include "../lib/lib.h"
# include <limits.h>
# include <stdint.h>

struct s_room;
struct s_route;

typedef struct			s_conn_wrap
{
	size_t				items;
	struct s_connection	**q;
	BITFIELD_TYPE		*visited;
}						t_conn_wrap;

typedef	struct			s_connection
{
	/* Last one that has conflicts */
	int						add;
	struct s_room			*src;
	struct s_room			*src_nb;
	struct s_room			*dst_nb;
	struct s_room			*dst;
	/* Distance to last conflict */
	size_t					dist;
	struct s_connection		*next;
	struct s_connection		*prev;
}						t_connection;

typedef struct			s_dupl
{
	struct s_connection	curr;
	struct s_connection	other;
	size_t				i;
	size_t				j;
}						t_dupl;

typedef struct			s_triangle
{
	struct s_connection	*src_side;
	struct s_connection	nb_src;
	struct s_connection	side_nb;
}						t_triangle;

typedef	struct 			s_diamond
{
	int					common_dst_found;
	size_t				nb_improved_by_side;
	size_t				side_improved_by_nb;
	struct s_connection	*src_side;
	struct s_connection	*nb_src;
	struct s_connection	*side_nb;
	struct s_connection	side_dst;
	struct s_connection	nb_dst;
	struct s_room 		*curr_nb_nb;
	struct s_room		*curr_nb_side;
}						t_diamond;

typedef struct			s_routeput
{
	char				 **rooms;
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

typedef struct			s_qnode
{
	struct s_room		*room;
	struct s_qnode		*next;
	struct s_qnode		*prev;
}						t_qnode;

typedef struct			s_qwrap
{
	struct s_qnode		*head;
	struct s_qnode		*tail;
}						t_qwrap;

typedef struct			s_room
{
	char				*name;
	int					sps;
	int					spe;
	int					is_junction;
	BITFIELD_TYPE		*removed_conns;
	ssize_t				xpos;
	ssize_t				ypos;
	size_t				ant;
	struct s_room		**neighbours;
	size_t				neighbours_len;
	size_t				conns_to;
	size_t				room_i;
	BITFIELD_TYPE		*bitroom;
	ssize_t				dist_to_end;
	ssize_t				dist_to_start;
}						t_room;
/*
** the structure of each room in the "ant hill"
*/

typedef struct			s_dfs_wrap
{
	struct s_route		*route;
	BITFIELD_TYPE		*visited;
	t_best				*candidate;
	const struct s_map	*map;
}						t_dfs_wrap;


typedef struct			s_map
{
	ssize_t				antmount;
	t_room				*start;
	t_room				*end;
	struct s_table		*rooms;
	BITFIELD_TYPE		*visited;
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
** UNNECESSARY TUBES REMOVE
*/
void					remove_dead_ends(t_map *map, int *changed);
void					remove_sps_spe_conns(t_map *map);
int						is_mutual_conn(t_room *curr, t_room *nb);
void					rm_un_conn(t_triangle *tr, t_map *map, int *changed);
ssize_t					remove_unnecessary_tubes(t_map *map, int *changed);
/*
** UNNECESSARY TUBES DUPLICATE PATHS
*/
void					remove_duplicate_paths(t_connection **conn, t_map *map,
int *changed);
/*
** UNNECESSARY TUBES QUEUE SETUP
*/
ssize_t					un_add_start_nbs_to_q(t_room *start,
											t_conn_wrap *qr,
											t_map *map,
											int *changed);
/*
** UNNECESSARY TUBES DELETE
*/
int						del_un_tubes(t_connection *q, int *changed, t_map *map);

/*
** UNNECESSARY TUBES QR UTILS
*/
ssize_t			setup_q_un(t_conn_wrap **qr, t_map *map);
void			free_q_un(t_conn_wrap **qr);
/*
** UNNECESSARY TUBES REMOVE IF UN
*/
void					remove_if_un(t_triangle *tr, t_map *map, int *changed);
/*
** UNNECESSARY TUBES QUEUE UPDATE
*/
ssize_t					un_add_nbs_to_queue(t_room *start, t_conn_wrap *qr,
												t_map *map, int *changed);
int						solve_queue_conflict(t_conn_wrap *qr, t_connection *tmp,
											t_map *map, size_t *added);
ssize_t					update_queue_un(t_conn_wrap *qr, t_map *map,int *changed);
/*
** UNNECESSARY TUBES QUEUE EXECUTE
*/
ssize_t					execute_queue_un(t_conn_wrap *qr, t_map *map, int *changed);
/*
** UNNECESSARY TUBES OPTION CHECKS
*/
int		is_junction(t_room *curr, t_map *map);
int						alt_opts_nb(t_triangle *curr,
												t_map *map,
												int *changed);
int						alt_opts_side(t_connection *side_nb,
												t_connection *src_side,
												t_map *map,
												int *changed);

/*
** UNNECESSARY TUBES NB CHECKS
*/
int						is_nb_of_src(t_triangle *curr,
												t_map *map,
												int *changed);
int						is_nb_of_other(t_room *dst,
												t_room *curr,
												t_map *map,
												int *changed);
/*
** UNNECESSARY TUBES SHORT CHECKS
*/
int						shrt_conn_dsts_side(t_connection *src_side,
													t_connection *nb_src,
													t_connection *side_nb);
int						shrt_conn_dsts_nb(t_connection *src_side,
													t_connection *nb_src,
													t_connection *side_nb);

/*
** UNNECESSARY TUBES UTILS
*/
int						check_conn(t_connection *conn, size_t *ind, int *changed, t_map *map);
size_t					handle_nowhere_to_go(t_room *src, t_room *nb, t_map *map);
size_t					kill_conn(t_room *src, t_room *nb, t_map *map);
size_t					remove_path(t_connection *conn, t_map *map);
size_t					handle_loop(t_connection *conn, t_map *map, int *changed);
void					set_conn(t_connection *conn, t_room *nb);
int						check_dst_src(t_connection *dst, t_connection *src,
										t_room *curr);
int						check_src(t_connection *conn, t_room *curr);
int						check_dest(t_connection *conn, t_room *curr);
void					setup_conn(t_connection *conn, t_room *src);
void					find_real_nb(t_connection *tmp);
int						del_tube(t_room *from, t_room *to, t_map *map);
t_connection			*new_connection(t_connection *item);
int						has_conn_to(t_room *curr, t_room *nb);
/*
** UNNECESSARY TUBES QUEUE
*/
ssize_t					add_q_item_un(t_conn_wrap *qr, t_connection *item, size_t *added, BITFIELD_TYPE *atq);
void					remove_q_item_un(t_conn_wrap *qr, t_connection *item);
/*
** ROUTE FINDING
*/
void					compare_candidate_best(t_map *map, t_best *candidate);
ssize_t					remove_blockage(t_best *candidate, t_map *map);
ssize_t					remove_conn(t_best *candidate, t_room *block, t_map *map);
ssize_t					setup_in_paths(t_best *candidate, BITFIELD_TYPE **in_paths,
										t_map *map);
ssize_t					alloc_multiple_blank_routes(t_route ***dst,
													const size_t route_num,
													const size_t route_len,
													const size_t bitroute_len);
ssize_t					alloc_single_blank_route(t_route **dst,
													const size_t route_len,
													const size_t bitroute_len);
size_t					better_eligible_candidate(const BITFIELD_TYPE *visited,
													const t_room *best_so_far,
													const t_room *candidate);
size_t					calc_cost(size_t ants, const t_best *routes);
ssize_t					exec_find_routes_df(t_room *curr,
											t_dfs_wrap *wrap);
ssize_t					find_routes(t_map *map);
ssize_t					find_routes_df(t_best *candidate, const t_map *map);
ssize_t					handle_err_route_finder(size_t err_code,
												const char *line);
ssize_t					traverse_bf(t_room *room_to_begin_from,
									const size_t call_code,
									const t_map *map);
ssize_t					max_parallels(size_t *result, const t_map *map);
t_room					*select_next_room(const t_room *curr,
											const t_dfs_wrap *wrap);

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

/*
** CLEANER
*/
void					delete_all_routes(t_map *map);
void					delete_all_rooms(t_table *rooms);
void					delete_map(t_map *map);

/*
** DEBUGGING
*/
void					print_connection_queue(t_connection **q);
void					print_map(t_map *map);
void					print_connection(t_connection *tmp);
void					print_best(const t_best *best);
void					print_rooms(const t_table *rooms);
void					print_neighbours(const t_room *room);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/23 19:24:52 by kim           #+#    #+#                 */
/*   Updated: 2020/08/11 14:55:04 by lravier       ########   odam.nl         */
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

typedef struct			s_find_routes_df_wrap
{
	BITFIELD_TYPE		*visited;
	BITFIELD_TYPE		*start_nb_visited;
	t_room				*shortest_dist_to_end;
	t_best				*candidate_best;
}						t_find_routes_df_wrap;

typedef struct            s_shortest_dist
{
	t_room				**nbs;
	t_room				*start;
	size_t				nbs_len;
	ssize_t				*nb_visited;
	ssize_t				nb_vis_i_of_ret;
	size_t				options_left;
}						t_shortest_dist;

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
int		is_mutual_conn(t_room *curr, t_room *nb);
int						rm_un_conn(t_connection *side_nb,
t_connection *src_side, t_connection *nb_src, t_map *map);
ssize_t					remove_unnecessary_tubes(t_map *map, int *changed);

/*
** UNNECESSARY TUBES QUEUE SETUP
*/
ssize_t					un_add_start_nbs_to_q(t_room *start,
											t_conn_wrap *qr,
											t_map *map,
											int *changed);
/*
** UNNECESSARY TUBES QUEUE UPDATE
*/
ssize_t					update_queue_un(t_conn_wrap *qr, t_map *map,int *changed);
/*
** UNNECESSARY TUBES OPTION CHECKS
*/
int		is_junction(t_room *curr, t_map *map);
int						alt_opts_nb(t_connection *side_nb,
												t_connection *src_side,
												t_connection *nb_src,
												t_map *map,
												int *changed);
int						alt_opts_side(t_connection *side_nb,
												t_connection *src_side,
												t_map *map,
												int *changed);

/*
** UNNECESSARY TUBES NB CHECKS
*/
int						is_nb_of_src(t_connection *side_nb,
												t_connection *src_side,
												t_connection *nb_src,
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
													t_connection *side_nb,
													t_map *map);
int						shrt_conn_dsts_nb(t_connection *src_side,
													t_connection *nb_src,
													t_connection *side_nb,
													t_map *map);

/*
** UNNECESSARY TUBES DELETE
*/
int						del_un_tubes(t_connection *q,
										int *changed,
										t_map *map);
/*
** UNNECESSARY TUBES UTILS
*/
int						handle_nowhere_to_go(t_room *src, t_room *nb, t_map *map);
void					handle_loop(t_connection *conn, t_map *map, int *changed, size_t *i);
void					handle_loop_no_ret(t_connection *conn, t_map *map, int *changed);
void					set_conn(t_connection *conn, t_room *nb);
int						check_dst_src(t_connection *dst, t_connection *src,
										t_room *curr);
int		check_src(t_connection *conn, t_room *curr);
int		check_dest(t_connection *conn, t_room *curr);
void	setup_conn(t_connection *conn, t_room *src);
void				find_real_nb(t_connection *tmp, t_map *map);
int				del_tube(t_room *from, t_room *to, t_map *map);
t_connection		*new_connection(t_connection *item);
int					has_conn_to(t_room *curr, t_room *nb);
/*
** UNNECESSARY TUBES QUEUE
*/
ssize_t			add_q_item_un(t_conn_wrap *qr, t_connection *item);
void			remove_q_item_un(t_conn_wrap *qr, t_connection *item);
/*
** ROUTE FINDING
*/
void					compare_state_best(t_map *map, t_best *state);
ssize_t					remove_blockage(t_best *state, t_map *map);
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
ssize_t					find_routes(t_map *map);
ssize_t					find_routes_df(t_best *state, t_map *map);
void					handle_err_branch_or_new(t_route **dst);
ssize_t					handle_err_route_finder(size_t err_code,
												const char *line);
ssize_t					handle_err_find_shortest_dist_option(
							t_shortest_dist *to_free);
ssize_t					init_find_route_df(t_find_routes_df_wrap *wrap,
											t_room *begin,
											const t_map *map);
ssize_t					traverse_bf(t_room *room_to_begin_from,
									const size_t call_code);
ssize_t					max_parallels(size_t *result, const t_map *map);
ssize_t				find_shortest_dist_option(t_room **ret_ptr,
												t_room *root,
												BITFIELD_TYPE *visited,
												t_shortest_dist *shortwrap);

/*
** BITFIELD-TOOLKIT
*/
void					merge_bitfield(BITFIELD_TYPE *dst,
										BITFIELD_TYPE *src,
										t_map *map);
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

#endif

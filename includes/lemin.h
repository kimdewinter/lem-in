/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/23 19:24:52 by kim           #+#    #+#                 */
/*   Updated: 2020/08/07 12:11:07 by lravier       ########   odam.nl         */
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

// typedef	struct			s_tube_cleaner
// {
// 	/* Last one that has conflicts */
// 	BITFIELD_TYPE			*in_route;
// 	struct s_room			*src;
// 	struct s_room			*dst;
// 	/* Distance to last conflict */
// 	size_t					dist;
// 	struct s_tube_cleaner	*prev;
// 	struct s_tube_cleaner	*next;
// }						t_tube_cleaner;

typedef struct 			s_weight
{
	size_t				weight;
	struct s_room		*dst;
	struct s_weight		*next;
}						t_weight;

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

typedef struct			s_room
{
	char				*name;
	int					sps;
	int					spe;
	int					is_junction;
	ssize_t				xpos;
	ssize_t				ypos;
	size_t				ant;
	size_t				weight;
	struct s_room		**neighbours;
	size_t				neighbours_len;
	size_t				room_i;
	BITFIELD_TYPE		*bitroom;
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
ssize_t					remove_unnecessary_tubes(t_map *map, int *changed);
ssize_t					create_q(void ***q, size_t size);
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
int						rm_un_conn(t_connection *side_nb,
t_connection *src_side, t_connection *nb_src, t_map *map);

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
int						alt_opts_nb(t_connection *side_nb,
												t_connection *src_side,
												t_connection *nb_src,
												t_map *map);
int						alt_opts_side(t_connection *side_nb,
												t_connection *src_side,
												t_connection *nb_src,
												t_map *map);

/*
** UNNECESSARY TUBES NB CHECKS
*/
int						is_nb_of_src(t_connection *side_nb,
												t_connection *src_side,
												t_connection *nb_src,
												t_map *map);
int						is_neighbour_of_other(t_room *dst,
												t_room *curr,
												t_map *map);
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
int					del_un_tubes(t_conn_wrap *qr,
										t_connection *q,
										int *changed,
										t_map *map);
/*
** UNNECESSARY TUBES UTILS
*/
void					handle_loop(t_connection *conn, t_map *map, int *changed, size_t *i);
void					set_conn(t_connection *conn, t_room *nb);
int						check_dst_src(t_connection *dst, t_connection *src,
										t_room *curr);
int		check_src(t_connection *conn, t_room *curr);
int		check_dest(t_connection *conn, t_room *curr);
void	setup_conn(t_connection *conn, t_room *src);
void				find_real_nb(t_room *src, t_connection *tmp, t_map *map);
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
ssize_t					set_weights(t_map *map, int flow);
ssize_t					find_routes(t_map *map);
ssize_t					handle_err_route_finder(size_t err_code,
												const char *line);
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
void					print_connection_queue(t_connection **q);
void					print_map(t_map *map);
void		print_connection(t_connection *tmp);
#endif

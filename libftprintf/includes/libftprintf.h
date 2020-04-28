/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libftprintf.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 10:55:17 by lravier        #+#    #+#                */
/*   Updated: 2020/02/29 15:19:19 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <wchar.h>
# include <fcntl.h>
# include <stdio.h>
# define INT "int"
# define U_INT "unsigned int"
# define U_CHAR "unsigned char"
# define W_INT "wint_t"
# define S_CHAR "signed char"
# define US_INT "unsigned short int"
# define S_INT "short int"
# define L_INT "long int"
# define UL_INT "unsigned long int"
# define LL_INT "long long int"
# define ULL_INT "unsigned long long int"
# define DOUBLE "double"
# define L_DOUBLE "long double"
# define STRING "const char *"
# define V_POINT "void *"
# define BUFF_SIZE 100
# define ARG_SIZE 12
# define INT_MIN -2147483648
# define INT_MAX_MIN -9223372036854775807LL - 1

typedef struct		s_pf_arg
{
	char			datatype[23];
	size_t			datasize;
	int				flags[5];
	int				field_width;
	int				precision;
	int				length_mods;
	char			conversion;
	int				conv_no;
	int				fw_no;
	int				prec_no;
	int				s_ind;
	int				end_ind;
	char			*tmp;
	int				len;
	void			*data;
	struct s_pf_arg	*next;
}					t_pf_arg;

typedef struct		s_vas
{
	char	**cpp;
	int		vas_size;
}					t_vas;

typedef struct		s_vd
{
	int fd;
}					t_vd;

typedef struct		s_vf
{
	FILE *fp;
}					t_vf;

typedef struct		s_vsn
{
	int				space;
	int				vsn_max;
	size_t			last_ind;
	char			*str;
}					t_vsn;

typedef union		u_wu
{
	struct s_vas	vas;
	struct s_vd		vd;
	struct s_vf		vf;
	struct s_vsn	vsn;
}					t_wu;

typedef struct		s_writer
{
	int				curr;
	int				len;
	union u_wu		u;
	int				(*ft_write)(char *src, int len, struct s_writer *wrt);
}					t_writer;

int					ft_write_output(t_pf_arg *instr, t_writer *wrt);

int					ft_write_vas(char *src, int len, t_writer *wrt);
int					ft_write_vd(char *src, int len, t_writer *wrt);
int					ft_write_vf(char *src, int len, t_writer *wrt);
int					ft_write_vsn(char *src, int len, t_writer *wrt);
int					ft_write_vs(char *src, int len, t_writer *wrt);

int					ft_vfprintf(FILE *stream, const char *format, va_list ap);
int					ft_fprintf(FILE *stream, const char *format, ...);

int					ft_vdprintf(int fd, const char *format, va_list ap);
int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
int					ft_vprintf(const char *format, va_list ap);

int					ft_vasprintf(char **ret, const char *format, va_list ap);
int					ft_asprintf(char **ret, const char *format, ...);

int					ft_vsnprintf(char *str, size_t size, const char *format,
va_list ap);
int					ft_sprintf(char *str, const char *format, ...);
int					ft_snprintf(char *str, size_t size,
const char *format, ...);
int					ft_vsprintf(char *str, const char *format, va_list ap);

int					ft_parse_format(const char *format,
t_pf_arg **instructions);

int					is_flag(char c);
int					is_conversion(char c);
void				if_is_conversion(const char *format, int *i,
int *curr, t_pf_arg *instr);
int					is_lm(char c);
int					is_number(char c);
int					is_valid(char c);

t_pf_arg			*initialize_arg(void);

int					get_result(t_pf_arg *instr, const char *format);

void				add_lm(const char *format, int *i, t_pf_arg *instr);
void				adjust_lm(t_pf_arg *instr);

void				add_flag(char c, int *i, t_pf_arg *instr);
void				if_is_number(const char *format, int *i, int *curr,
t_pf_arg *instr);
void				if_is_asterisk(const char *format, int *i, int *curr,
t_pf_arg *instr);

void				ft_pflstaddend(t_pf_arg *elem, t_pf_arg **instructions);

int					ft_pferror(char *str);

int					adjust_flags_precision(t_pf_arg **instr);

int					ft_create_arguments(t_pf_arg **instructions, va_list args);
void				check_double(int dbl, va_list args);

size_t				get_size_of_datatype(char *datatype);

int					ft_set_data(va_list args, t_pf_arg *tmp);

void				set_datatype(t_pf_arg *instr);

void				set_default_prec(t_pf_arg *instr);
void				skip_digits(const char *str, int *i);

void				if_is_period(const char *format, int *i, int *curr,
t_pf_arg *instr);

void				check_range(t_pf_arg **instructions, int high, int *range);
void				find_highest(t_pf_arg **instructions, int *high);

int					ft_dispatcher(t_pf_arg **instructions, const char *format,
t_writer *wrt);

int					ft_handle_di(t_pf_arg *instr);
int					ft_handle_o(t_pf_arg *instr);
int					ft_handle_u(t_pf_arg *instr);
int					ft_handle_x(t_pf_arg *instr);
int					ft_handle_b(t_pf_arg *instr);
int					ft_handle_p(t_pf_arg *instr);
int					ft_handle_c(t_pf_arg *instr);
int					ft_handle_wint(t_pf_arg *instr);
int					ft_handle_f(t_pf_arg *instr);
int					ft_handle_e(t_pf_arg *instr);
int					ft_handle_s(t_pf_arg *instr);
int					ft_handle_empty(t_pf_arg *instr, const char *format);
int					ft_handle_g(t_pf_arg *instr);

int					ft_strnull(t_pf_arg *instr);

int					get_int_len(intmax_t num, t_pf_arg *instr, int base);

uintmax_t			get_unsigned_number(t_pf_arg *instr);
intmax_t			get_number(t_pf_arg *instr);
long double			get_double(t_pf_arg *instr);

void				put_nbr(intmax_t num, t_pf_arg *instr, int len, int base);
void				put_nbr_u(uintmax_t num, t_pf_arg *instr,
int len, int base);

int					get_int_len_u(uintmax_t num, t_pf_arg *instr, int base);

int					has_alt_form(char c);
int					is_signed_conversion(char c);
int					is_dioux(char c);
int					is_numeric_conversion(char c);

void				set_int(va_list args, t_pf_arg *tmp);
void				set_uint(va_list args, t_pf_arg *tmp);
void				set_uchar(va_list args, t_pf_arg *tmp);
void				set_schar(va_list args, t_pf_arg *tmp);
void				set_usint(va_list args, t_pf_arg *tmp);
void				set_sint(va_list args, t_pf_arg *tmp);
void				set_lint(va_list args, t_pf_arg *tmp);
void				set_ulint(va_list args, t_pf_arg *tmp);
void				set_llint(va_list args, t_pf_arg *tmp);
void				set_ullint(va_list args, t_pf_arg *tmp);
void				set_wint(va_list args, t_pf_arg *tmp);
void				set_vpoint(va_list args, t_pf_arg *tmp);
void				set_ldouble(va_list args, t_pf_arg *tmp);
int					set_string(va_list args, t_pf_arg *tmp);
void				set_double(va_list args, t_pf_arg *tmp);
#endif

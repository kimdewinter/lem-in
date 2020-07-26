/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floats.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 14:15:50 by lravier        #+#    #+#                */
/*   Updated: 2020/02/29 15:18:55 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOATS_H
# define FLOATS_H
# include <stdio.h>
# include <math.h>
# include <stdint.h>
# include <stdlib.h>
# include "../../includes/libftprintf.h"
# define BASE 1000000
# define OFFSET 16383
# define DECPLB 6
# define ARR 128

typedef struct	s_bigint
{
	uint32_t	big[128];
	int			biggest_exp;
	int			sign;
	int			startind;
	int			zeros;
}				t_bigint;

int				get_maxind(t_bigint *val, t_pf_arg *instr, int mult);
void			ft_get_len_f(t_pf_arg *instr, t_bigint *val);
int				ft_make_output(t_pf_arg *instr, t_bigint *val, long int exp);
void			shift_left(uint32_t *remainder, t_bigint *val);
void			ft_round_e(t_bigint *val, t_pf_arg *instr, int *fact,
int *mult);
void			ft_get_startind(t_bigint *val);
int				ft_add_len_fact(int fact);
void			ft_add_exp(t_pf_arg *instr, int fact, int i);
int				ft_frexp(long double n, long int *exp, t_bigint *val,
long long unsigned *mnt);
int				ft_get_string(t_pf_arg *instr, long double num);
int				ft_isnan(long double x);
int				ft_isinf(long double x);
long int		ft_abs(long int n);
void			ft_create_bigint(unsigned long long n, long int exp,
t_bigint *val);
int				ft_mult_bigint(t_bigint *val, long int exp);
int				ft_div_bigint(t_bigint *val, long int exp);
void			ft_round_bigint(t_bigint *val, int prec, t_pf_arg *instr);
int				ft_create_string(t_pf_arg *instr, t_bigint *val);
void			ft_first_place(t_pf_arg *instr, t_bigint val, int *j);
void			ft_start_fact(uint32_t *fract, uint32_t *factor, t_bigint val);
void			ft_fill_dec(t_pf_arg *instr, t_bigint val, int *j);
int				ft_scale_bigint(t_bigint *val, t_pf_arg *instr, int *fact,
long int exp);
int				ft_create_string_e(t_pf_arg *instr, t_bigint *val, int mult,
int fact);
int				get_len_zero_excep(t_pf_arg *instr, int len, t_bigint *val);
int				ft_zero_string(t_pf_arg *instr, t_bigint *val);
int				ft_string_exceptions(long double num, t_pf_arg *instr,
t_bigint *val);
int				ft_conv_g(t_pf_arg *instr, t_bigint *val, long int exp);
void			ft_adjust_precision(t_pf_arg *instr, t_bigint *val);
#endif

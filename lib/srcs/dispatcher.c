/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dispatcher.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/06 14:41:15 by lravier       #+#    #+#                 */
/*   Updated: 2020/04/28 11:40:54 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

static void	free_arg(t_pf_arg **instr)
{
	if ((*instr)->tmp)
	{
		free((*instr)->tmp);
		(*instr)->tmp = NULL;
	}
	if ((*instr)->data)
	{
		free((*instr)->data);
		(*instr)->data = NULL;
	}
	free(*instr);
}

static int	calc_len(const char *format, int i, int *state)
{
	int		j;
	int		len;

	j = i;
	while (format[j] && !(format[j] == '%' && !(*state)))
	{
		*state = 0;
		j++;
	}
	len = j - i;
	return (len);
}

static int	ft_write_arg(t_pf_arg **instr, t_writer *wrt,
int *state, int *i)
{
	t_pf_arg *prev;

	if (!ft_write_output(*instr, wrt))
		return (0);
	*i = (*instr)->end_ind;
	*state = 0;
	prev = *instr;
	*instr = (*instr)->next;
	free_arg(&prev);
	return (1);
}

static int	ft_write_frm(t_writer *wrt, const char *format,
int *i, int *state)
{
	wrt->len = calc_len(format, *i, state);
	if (!wrt->ft_write((char *)&format[*i], wrt->len, wrt))
		return (0);
	*i += wrt->len;
	if (wrt->len == 0)
		*state = 1;
	return (1);
}

int			ft_dispatcher(t_pf_arg **instructions,
const char *format, t_writer *wrt)
{
	t_pf_arg	*instr;
	int			i;
	int			state;

	i = 0;
	state = 0;
	instr = *instructions;
	while (format[i])
	{
		wrt->len = 0;
		if (instr && instr->s_ind == i)
		{
			if (!(get_result(instr, format) &&
			ft_write_arg(&instr, wrt, &state, &i)))
				return (0);
		}
		else
		{
			if (!ft_write_frm(wrt, format, &i, &state))
				return (0);
		}
		if (!wrt->len && format[i])
			i++;
	}
	return (1);
}

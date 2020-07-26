/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_create_argument.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/07 11:40:09 by lravier        #+#    #+#                */
/*   Updated: 2019/11/11 11:31:42 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

t_pf_arg	*initialize_arg(void)
{
	t_pf_arg *elem;

	elem = (t_pf_arg *)malloc(sizeof(t_pf_arg));
	if (!elem)
		return (NULL);
	ft_bzero(elem->flags, sizeof(elem->flags));
	ft_bzero(elem->datatype, sizeof(elem->datatype));
	elem->field_width = 0;
	elem->precision = -1;
	elem->length_mods = 0;
	elem->conversion = '0';
	elem->conv_no = 0;
	elem->fw_no = 0;
	elem->prec_no = 0;
	elem->s_ind = 0;
	elem->end_ind = 0;
	elem->datasize = 0;
	elem->tmp = NULL;
	elem->len = 0;
	elem->data = NULL;
	elem->next = NULL;
	return (elem);
}

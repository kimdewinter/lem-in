/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   link_rooms.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:39:07 by kim           #+#    #+#                 */
/*   Updated: 2020/04/29 17:32:41 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"
# include "../libftprintf/includes/libftprintf.h"
# include "../libftprintf/libft/libft.h"
# include "../libftprintf/libft/get_next_line.h"

static size_t	is_duplicate_link(const t_room *alpha, const t_room *omega)
{
	size_t	i;

	i = 0;
	if (alpha->links_len < 1 && omega->links_len < 1)
		return (0);
	while (i < alpha->links_len)
	{

	}

	return (1);
}

ssize_t	link_rooms(t_room *alpha, t_room *omega)
{
	
	return (EXIT_FAILURE);
}

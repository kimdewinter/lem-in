/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lravier <lravier@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/20 10:54:55 by lravier       #+#    #+#                 */
/*   Updated: 2020/09/30 13:19:11 by lravier       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_error(char *str, int n)
{
	ft_putstr_fd(str, STDERR_FILENO);
	return (n);
}

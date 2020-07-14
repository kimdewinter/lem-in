/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parallelizer_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 13:43:11 by kim           #+#    #+#                 */
/*   Updated: 2020/07/14 16:05:18 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

ssize_t	expand_comvault(t_comvault *comvault)
{
	size_t		i;
	size_t		new_coms_len;
	t_poscom	**new_coms;

	i = 0;
	new_coms_len = comvault->coms_len * COMVAULT_LEN_INCR_MULT;
	new_coms = (t_poscom **)malloc(sizeof(t_poscom *) * new_coms_len);
	if (new_coms == NULL)
		return (EXIT_FAILURE);
	while (i < comvault->coms_used)
	{
		new_coms[i] = comvault->coms[i];
		i++;
	}
	while (i < new_coms_len)
	{
		new_coms[i] = NULL;
		i++;
	}
	free(comvault->coms);
	comvault->coms = new_coms;
	comvault->coms_len = new_coms_len;
	return (EXIT_SUCCESS);
}

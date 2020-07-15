/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parallelizer_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 13:43:11 by kim           #+#    #+#                 */
/*   Updated: 2020/07/15 17:22:44 by kim           ########   odam.nl         */
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

ssize_t			commit_best(const t_poscom *bestcom, t_best *new_entry)
{
	if (bestcom == NULL)
		return (EXIT_FAILURE);
	new_entry->len = bestcom->num_routes;
	new_entry->combi =
		(t_route **)malloc(sizeof(t_route *) * new_entry->len);
	if (new_entry->combi == NULL)
		return (handle_err_comtron(1, "commit_best\n"));
	new_entry->used = 0;
	while (new_entry->used < bestcom->num_routes)
	{
		new_entry->combi[new_entry->used] = bestcom->routes[new_entry->used];
		new_entry->used++;
	}
	new_entry->turns = bestcom->turns;
	return (EXIT_SUCCESS);
}

inline static void	delete_poscom(t_poscom *poscom)
{
	if (poscom->routes != NULL)
	{
		free(poscom->routes);
		poscom->routes = NULL;
	}
	if (poscom->bitroutes != NULL && poscom->num_routes > 1)
	{
		free(poscom->bitroutes);
		poscom->bitroutes = NULL;
	}
	else if (poscom->bitroutes != NULL && poscom->num_routes <= 1)
		poscom->bitroutes = NULL;
	poscom->num_routes = 0;
}

static void			delete_single_comvault(t_comvault *comvault)
{
	size_t	i;

	if (comvault->coms != NULL)
	{
		i = 0;
		while (i < comvault->coms_used)
		{
			if (comvault->coms[i] != NULL)
			{
				delete_poscom(comvault->coms[i]);
				free(comvault->coms[i]);
				comvault->coms[i] = NULL;
			}
			i++;
		}
		free(comvault->coms);
		comvault->coms = NULL;
		comvault->coms_len = 0;
		comvault->coms_used = 0;
	}
}

void			delete_all_comvaults(t_comvault **comvaults, const size_t len)
{
	size_t	i;

	if (comvaults != NULL)
	{
		i = 0;
		while (i < len)
		{
			if (comvaults[i] != NULL)
			{
				delete_single_comvault(comvaults[i]);
				free(comvaults[i]);
				comvaults[i] = NULL;
			}
			i++;
		}
	}
}

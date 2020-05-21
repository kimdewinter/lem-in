/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   biter.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kim <kim@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/20 15:13:42 by kim           #+#    #+#                 */
/*   Updated: 2020/05/21 14:13:51 by kim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

ssize_t			bite_room(t_room *room,
							const size_t rooms_amount,
							const size_t room_index)
{
	size_t	i;
	size_t	bitfield_len;

	if (room != NULL && room->bitroom == NULL)
	{
		bitfield_len = rooms_amount / BITFIELD_SIZE + 1;
		room->bitroom = (BITFIELD_TYPE *)malloc(
			sizeof(BITFIELD_TYPE) * bitfield_len);//allocates too much in case of exact size-match, e.g. rooms_amount is 64/128/etc
		if (room->bitroom != NULL)
		{
			i = 0;
			while (i < bitfield_len)
			{
				room->bitroom[i] = (i == room_index / BITFIELD_SIZE) ?
					(BITFIELD_TYPE)1 << 63 - room_index % BITFIELD_SIZE:
					(BITFIELD_TYPE)0;
				i++;
			}
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_listfuncs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:56:09 by femaury           #+#    #+#             */
/*   Updated: 2018/06/11 14:57:12 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
 * 		t_room	*find_room(t_room *rooms, char *name);
 *
 *	  Finds room in linked list with corresponding name.
 *	  If no room is found, returns NULL so that a call to
 *	  lem_in_exit can be made from parent function.
 *
*/

t_room	*find_room(t_room *rooms, char *name)
{
	t_room	*curr;

	curr = rooms;
	while (curr)
	{
		if (!ft_strcmp(curr->name, name))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

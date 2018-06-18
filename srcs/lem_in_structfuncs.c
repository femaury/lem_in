/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_structfuncs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:56:09 by femaury           #+#    #+#             */
/*   Updated: 2018/06/18 15:07:54 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** 		t_room	*find_room(t_room *rooms, char *name);
**
**	Finds room in linked list with corresponding name.
**	If no room is found, returns NULL so that a call to
**	lem_in_exit can be made from parent function.
**
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

/*
** 		void	env_init(t_env *env);
**
**	Initializes the program's environment.
**	
*/

void	env_init(t_env *env)
{
	env->error = 0;
	env->pop = 0;
	env->best_len = UINT_MAX;
	env->file = NULL;
	env->start = NULL;
	env->end = NULL;
	env->del = NULL;
	env->tmp = NULL;
	env->best = NULL;
	env->ants = NULL;
	env->rooms = NULL;
}

void	ant_del(t_ant **ants)
{
	if (!*ants)
		return ;
	ant_del(&(*ants)->next);
	free(*ants);
	*ants = NULL;
}

void	room_del(t_room **rooms)
{
	if (!*rooms)
		return ;
	room_del(&(*rooms)->next);
	ft_strdel(&(*rooms)->name);
	ft_lstdel(&(*rooms)->links);
	free(*rooms);
	*rooms = NULL;
}

void	link_best_room(t_env *env)
{
	t_room	*room;
	t_list	*curr;

	curr = env->best->next;
	env->best_room = find_room(env->rooms, env->start);
	room = env->best_room;
	while (curr)
	{
		room->best = find_room(env->rooms, (char *)curr->content);
		room = find_room(env->rooms, (char *)curr->content);
		curr = curr->next;
	}
}

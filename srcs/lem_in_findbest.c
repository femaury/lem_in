/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_findbest.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 13:06:20 by femaury           #+#    #+#             */
/*   Updated: 2018/06/14 12:41:37 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
 *		int	find_end(t_env *env, t_room *curr, t_list *tunnel, unsigned len);
 *
 *	Recursive function that finds the lenght of the shortest path from start to
 *	end and saves it to env->best_len.
 *
 *	TO DO:
 *		Save in env->best the names of all the rooms in the shortest path found.
 *
*/

static void	find_end(t_env *env, t_room *curr, t_list *tunnel, unsigned len)
{
	if (curr)
	{
		curr->status = curr->status == EMPTY ? OCCUPIED : curr->status;
		tunnel = curr->links;
		if (ft_lstfind_content(tunnel, env->end))
		{
			if (len < env->best_len)
			{
				env->best_len = len;
				ft_lstappend(&env->tmp, ft_lstnew(curr->name, ft_strlen(curr->name)));
				env->best = ft_lstcpy(&env->tmp);
				ft_lstdellast(&env->tmp);
			}
			curr->status = EMPTY;
			return ;
		}
		while (tunnel)
		{
			if (find_room(env->rooms, tunnel->content)->status == EMPTY)
			{
				if (curr != find_room(env->rooms, env->start)
						&& !ft_lstfind_content(env->tmp, curr->name))
					ft_lstappend(&env->tmp, ft_lstnew(curr->name, ft_strlen(curr->name)));
				find_end(env, find_room(env->rooms, tunnel->content), NULL, len + 1);
			}
			tunnel = tunnel->next;
		}
		curr->status = curr->status == OCCUPIED ? EMPTY : curr->status;
		ft_lstdellast(&env->tmp);
	}
}

/*
 *		void	find_best_path(t_env *env);
 *
 *	Initializes env->best and env->best_len to
 *	then call find_end.
 *
*/

void	find_best_path(t_env *env)
{
	t_room	*start;

	env->best_len = UINT_MAX;
	start = find_room(env->rooms, env->start);
	if (!(env->tmp = ft_lstnew(env->start, ft_strlen(env->start))))
		lem_in_exit();
	find_end(env, start, NULL, 1);
	ft_lstdel(&env->tmp);
	if (!env->best)
		lem_in_exit();
}

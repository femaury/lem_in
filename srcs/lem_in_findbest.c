/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_findbest.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 13:06:20 by femaury           #+#    #+#             */
/*   Updated: 2018/06/11 19:38:30 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
 *		int	find_end(t_env *env, t_room *curr, t_list *tunnel, unsigned len);
 *
 *	Recursive function that finds the shortest path from start to end and saves
 *	it to env->best_len.
 *
 *	TO DO:
 *		Save in env->best the names of all the rooms in the shortest path found.
 *
*/
static int	find_end(t_env *env, t_room *curr, t_list *tunnel, unsigned len)
{
	if (curr)
	{
		curr->status = curr->status == EMPTY ? OCCUPIED : curr->status;
		tunnel = curr->links;
		if (ft_lstfind_content(tunnel, env->end))
		{
			env->best_len = len < env->best_len ? len : env->best_len;
			curr->status = EMPTY;
			return (1);
		}
		while (tunnel)
		{
			if (find_room(env->rooms, tunnel->content)->status == EMPTY)
			{
//				ft_lstadd(&env->best, ft_lstnew(curr->name, ft_strlen(curr->name)));
				find_end(env, find_room(env->rooms, tunnel->content), NULL, len + 1);
			}
			tunnel = tunnel->next;
		}
	}
	curr->status = curr->status == OCCUPIED ? EMPTY : curr->status;
	return (0);
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
	if (!(env->best = ft_lstnew(env->start, ft_strlen(env->start))))
		lem_in_exit();
	find_end(env, start, NULL, 1);
}

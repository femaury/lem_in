/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_findbest.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 13:06:20 by femaury           #+#    #+#             */
/*   Updated: 2018/06/18 20:00:07 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**		void	save_path(t_env *env, t_room *curr, unsigned len);
**
**	Adds current room to end of tmp list. Saves shortest path found by
**	copying env->tmp to env->best and saves its length in env->best_len.
**	Removes current room from tmp list and sets it back to EMPTY (backtrack).
*/

static void	save_path(t_env *env, t_room *curr, unsigned len)
{
	t_list	*del;

	if (len < env->best_len)
	{
		env->best_len = len;
		if (!ft_lstfind_content(env->tmp, curr->name))
			ft_lstappend(&env->tmp, ft_lstnew(curr->name,
						ft_strlen(curr->name) + 1));
		del = env->best;
		env->best = ft_lstcpy(&env->tmp);
		if (del)
			ft_lstdel(&del);
		ft_lstdellast(&env->tmp);
	}
	curr->status = EMPTY;
}

/*
**		int	find_end(t_env *env, t_room *curr, t_list *tunnel, unsigned len);
**
**	Recursive function that checks all possible paths from START to END and
**	calls save_path every time it finds a shorter path. Each time you enter
**	a room, you set it to OCCUPIED and save the previous room in the tmp list.
*/

static void	find_end(t_env *env, t_room *curr, t_list *tunnel, unsigned len)
{
	if (curr)
	{
		curr->status = curr->status == EMPTY ? OCCUPIED : curr->status;
		tunnel = curr->links;
		if (ft_lstfind_content(tunnel, env->end))
		{
			save_path(env, curr, len);
			return ;
		}
		while (tunnel)
		{
			if (find_room(env->rooms, (char *)tunnel->content)->status == EMPTY)
			{
				if (!ft_lstfind_content(env->tmp, curr->name))
					ft_lstappend(&env->tmp, ft_lstnew(curr->name,
								ft_strlen(curr->name) + 1));
				find_end(env, find_room(env->rooms,
							(char *)tunnel->content), NULL, len + 1);
			}
			tunnel = tunnel->next;
		}
		curr->status = curr->status == OCCUPIED ? EMPTY : curr->status;
		ft_lstdellast(&env->tmp);
	}
}

/*
**		void	find_best_path(t_env *env);
**
**	Initializes env->best and env->best_len to
**	then call find_end.
*/

void		find_best_path(t_env *env)
{
	t_room	*start;

	start = find_room(env->rooms, env->start);
	if (!(env->tmp = ft_lstnew(env->start, ft_strlen(env->start) + 1)))
		lem_in_exit(E_MALLOC);
	find_end(env, start, NULL, 1);
	ft_lstappend(&env->best, ft_lstnew(env->end, ft_strlen(env->end) + 1));
	ft_lstdel(&env->tmp);
	if (!env->best)
		lem_in_exit(E_NOPATH);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_findbest.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 13:06:20 by femaury           #+#    #+#             */
/*   Updated: 2018/06/11 16:45:51 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	find_end(t_env *env, t_room *curr, t_list *tunnel, unsigned len)
{
	if (curr)
	{
		tunnel = curr->links;
		if (ft_lstfind_content(tunnel, env->end) && len < env->best_len)
		{
			ft_printf("Found new best!\n");
			if (!env->best)
				ft_lstdel(env->best);
			env->best_len = len;
			if (!(env->best = ft_lstnew(env->end, ft_strlen(env->end))))
				lem_in_exit();
			ft_lstadd(&env->best, ft_lstnew(curr->name, ft_strlen(curr->name)));
			return (1);
		}
		while (tunnel)
		{
			ft_printf("Calling self with %s\n", (char *)tunnel->content);
			if (find_end(env, find_room(env->rooms, tunnel->content), NULL, ++len))
			{
				ft_lstadd(&env->best, ft_lstnew(curr->name, ft_strlen(curr->name)));
				return (1);
			}
			tunnel = tunnel->next;
		}
	}
	return (0);
}

void	find_best_path(t_env *env)
{
	t_room	*start;

	start = find_room(env->rooms, env->start);
	find_end(env, start, NULL, 1);
}

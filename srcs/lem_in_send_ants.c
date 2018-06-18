/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_send_ants.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:01:05 by femaury           #+#    #+#             */
/*   Updated: 2018/06/18 17:45:24 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	move(t_env *env, t_room *curr, unsigned *arrived)
{
	if (curr->status == END)
	{
	   *arrived += 1;
	   return ;
	}
	if (curr->status == EMPTY)
		return ;
	move(env, curr->best, arrived);
	curr->best->status = curr->best->status == EMPTY ? OCCUPIED : curr->best->status;
	curr->best->ant_id = curr->ant_id;
}

static void	print_ants(t_env *env)
{
	t_room	*curr;

	curr = env->best_room;
	while (curr)
	{
		if (curr->status != START && curr->ant_id)
			ft_printf("L%u-%s ", curr->ant_id, curr->name);
		curr = curr->best;
	}
	ft_printf("\n");
}

void		send_ants(t_env *env)
{
	unsigned int	departed;
	unsigned int	arrived;
	t_room			*curr;

	arrived = 0;
	departed = 0;
	while (arrived < env->pop)
	{
		curr = env->best_room;
		curr->ant_id = departed < env->pop ? departed + 1: 0;
		if (departed == env->pop + 1)
			while (curr->status != END && curr->status != OCCUPIED)
				curr = curr->best;
		move(env, curr, &arrived);
		print_ants(env);
		departed++;
	}
}

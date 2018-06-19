/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_send_ants.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:01:05 by femaury           #+#    #+#             */
/*   Updated: 2018/06/19 11:54:26 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**		void	move(t_env *env, t_room *curr, unsigned *arrived);
**
**	Recursive function that iterates over the shortest path t_room list
**	until it either finds END or an empty room and then moves all the ants
**	up to that room, setting it to OCCUPIED.
*/

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
	curr->best->status = curr->best->status == EMPTY
		? OCCUPIED : curr->best->status;
	curr->best->ant_id = curr->ant_id;
}

/*
**		void	print_ants(t_env *env);
**
**	Function that prints which ants are where.
*/

static void	print_ants(t_room *curr)
{
	if (!curr)
		return ;
	print_ants(curr->best);
	if (curr->status != START && curr->ant_id)
		ft_printf("L%u-%s ", curr->ant_id, curr->name);
}

/*
**		void	send_ants(t_env *env);
**
**	Function that loops until all ants have
**	arrived in END room, calling move and print_ants.
*/

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
		curr->ant_id = departed < env->pop ? departed + 1 : 0;
		if (departed == env->pop + 1)
			while (curr->status != END && curr->status != OCCUPIED)
				curr = curr->best;
		move(env, curr, &arrived);
		print_ants(env->best_room);
		ft_printf("\n");
		departed++;
	}
}

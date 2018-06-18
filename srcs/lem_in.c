/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:15:12 by femaury           #+#    #+#             */
/*   Updated: 2018/06/18 20:31:12 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**		void	send_to_end(t_env *env);
**
**	Prints all ants going from start to end.
*/

void	send_to_end(t_env *env)
{
	unsigned int	pop;

	pop = env->pop;
	while (pop > 0)
		ft_printf("L%u-%s ", pop--, env->end);
	ft_printf("\n");
}

/*
**		MAIN FUNCTION
**
**	Initializes environment.
**	Calls parse_input to
**	finish creating the env.
*/

int		main(void)
{
	t_env	env;

	env_init(&env);
	parse_input(&env);
	if (!env.start)
		lem_in_exit(env.error = E_NOSTART);
	if (!env.end)
		lem_in_exit(env.error = E_NOEND);
	find_best_path(&env);
	ft_putendl(env.file);
	ft_printf("\n");
	link_best_room(&env);
	if (env.best_len == 1)
		send_to_end(&env);
	else
		send_ants(&env);
	ant_del(&env.ants);
	room_del(&env.rooms);
	ft_lstdel(&env.best);
	ft_strdel(&env.file);
	return (0);
}

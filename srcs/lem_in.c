/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:15:12 by femaury           #+#    #+#             */
/*   Updated: 2018/06/09 19:04:13 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_lists(t_env *env)
{
	t_room	*room;
	t_ant	*ant;

	ft_printf("\n{CYAN}------------------------------ ANTS ------------------------------{EOC}\n\n");
	ant = env->ants;
	ft_printf("-----> TOTAL POPULATION OF %u ANTS <-----\n\n", env->pop);
	while (ant)
	{
		ft_printf("Ant ID: %u found.\n", ant->id);
		ant = ant->next;
	}
	ft_printf("\n{CYAN}------------------------------ HILL ------------------------------{EOC}\n\n");
	room = env->rooms;
	while (room)
	{
		ft_printf("--------------------\n");
		ft_printf("|                  |\n");
		ft_printf("|   NAME: %s        |\n", room->name);
		ft_printf("|   COOR: (%02d, %02d) |\n", room->posx, room->posy);
		ft_printf("|   STAT: %d        |\n", room->status);
		ft_printf("|   ANT : %u        |\n", room->ant_id);
		ft_printf("|                  |\n");
		ft_printf("--------------------\n\n");
		ft_printf("          |\n");
		ft_printf("          |\n");
		ft_printf("          |\n");
		ft_printf("          V\n");
		room = room->next;
	}
}

int		main(void)
{
	t_env	env;

	env.pop = 0;
	env.ants = NULL;
	env.rooms = NULL;
	parse_input(&env);
	print_lists(&env);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:15:12 by femaury           #+#    #+#             */
/*   Updated: 2018/06/10 12:55:09 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
 *		TEST FUNCTION
 *
 *	Prints the results of parse_input
 *	to verify correct parsing.
 *
*/

void	print_lists(t_env *env)
{
	t_list	*link;
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
		ft_printf("---------------------\n");
		ft_printf("                   \n");
		ft_printf("   NAME  : %s        \n", room->name);
		ft_printf("   COORDS: (%02d, %02d) \n", room->posx, room->posy);
		ft_printf("   STATUS: %d        \n", room->status);
		ft_printf("   ANT ID: %u        \n", room->ant_id);
		ft_printf("   LINKS           \n");
		link = room->links;
		while (link)
		{
			ft_printf("    |-> %s          \n", (char *)link->content);
			link = link->next;
		}
		ft_printf("                   \n");
		ft_printf("---------------------\n");
		ft_printf("          |\n");
		ft_printf("          |\n");
		ft_printf("          |\n");
		ft_printf("          V\n");
		room = room->next;
	}
}

/*
 *		MAIN FUNCTION
 *
 *	Initializes environment.
 *	Calls parse_input to
 *	finish creating the env.
 *
*/

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

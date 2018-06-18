/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:15:12 by femaury           #+#    #+#             */
/*   Updated: 2018/06/18 19:13:13 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**		TEST FUNCTION
**
**	Prints the results of parse_input
**	to verify correct parsing.
**
*/

void	print_lists(t_env *env)
{
//	t_list	*link;
	t_room	*room;
//	t_ant	*ant;

/*	ft_printf("\n{CYAN}------------------------------ ANTS ------------------------------{EOC}\n\n");
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
*/	room = env->best_room;
//	ft_printf("      \\_______/      \n\n");
	ft_printf("START --> %s\nEND ----> %s\n\n", env->start, env->end);
	ft_printf("FOUND SHORTEST PATH OF LEN %u\n\n", env->best_len);
	while (room->best)
	{
		ft_printf("%s  -->  ", room->name);
		room = room->best;
	}
	ft_printf("%s\n\n", room->name);
}

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
**
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
//	print_lists(&env);
	if (env.best_len == 1)
		send_to_end(&env);
	else
		send_ants(&env);
	ant_del(&env.ants);
	room_del(&env.rooms);
	ft_strdel(&env.file);
	return (0);
}

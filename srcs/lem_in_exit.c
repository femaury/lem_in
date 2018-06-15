/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 18:55:45 by femaury           #+#    #+#             */
/*   Updated: 2018/06/15 16:28:11 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** 		void	lem_in_exit(void);
**
**	Called when program needs to exit.
**	
**	TO-DO:
**		Receives error number allowing
**		function to free allocated
**		memory before exiting.
**
*/

void	lem_in_exit(int error)
{
	if (error == E_MALLOC || error == E_SPLIT)
		ft_printf("{RED}ERROR{EOC}\nStopped program."
				" Insufficient memory during call to malloc.\n");
	else if (error == E_NOPOP)
		ft_printf("{RED}ERROR{EOC}\nStopped program."
				" No population size found.\n");
	else if (error == E_NOPATH)
		ft_printf("{RED}ERROR{EOC}\nStopped program."
				" No path found from start to end.\n");
	else if (error == E_NOSTART || error == E_NOEND)
		ft_printf("{RED}ERROR{EOC}\nStopped program. No %s room found.\n",
				error == E_NOEND ? "end" : "start");
	exit(error);
}

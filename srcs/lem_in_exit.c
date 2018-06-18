/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 18:55:45 by femaury           #+#    #+#             */
/*   Updated: 2018/06/18 20:29:22 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** 		void	lem_in_exit(int error);
**
**	Called when program needs to exit. Returns
**	proper error messages.
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

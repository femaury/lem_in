/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 18:55:45 by femaury           #+#    #+#             */
/*   Updated: 2018/06/10 12:50:56 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
 * 		void	lem_in_exit(void);
 *
 *	Called when program needs to exit.
 *	
 *	TO-DO:
 *		Receives error number allowing
 *		function to free allocated
 *		memory before exiting.
 *
*/

void	lem_in_exit(void)
{
	exit(1);
}

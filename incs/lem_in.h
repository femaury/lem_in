/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 15:49:58 by femaury           #+#    #+#             */
/*   Updated: 2018/06/11 16:32:45 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

/*
 *	----------------------------- SYSTEM LIBRARIES -----------------------------
*/

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <stdio.h>

/*
 *	------------------------------- MY LIBRARIES -------------------------------
*/

# include "../libs/libft/incs/libft.h"
# include "../libs/printf/incs/libftprintf.h"

/*
 *	------------------------------ STATUS DEFINES ------------------------------
*/

# define EMPTY 0
# define OCCUPIED 1
# define START 2
# define END 3

/*
 *	-------------------------------- STRUCTURES --------------------------------
*/

typedef struct	s_ant
{
	unsigned int	id;
	struct s_ant	*next;
	struct s_room	*room;
}				t_ant;

typedef struct	s_room
{
	char			*name;
	int				status;
	int				posx;
	int				posy;
	unsigned int	ant_id;
	t_list			*links;
	struct s_room	*next;
}				t_room;

typedef struct	s_env
{
	char			*start;
	char			*end;
	unsigned int	pop;
	unsigned int	best_len;
	t_list			*best;
	struct s_ant	*ants;
	struct s_room	*rooms;
}				t_env;

/*
 *	----------------------------- LEM_IN FUNCTIONS -----------------------------
*/

void			parse_input(t_env *env);
void			find_best_path(t_env *env);
void			lem_in_exit(void);

/*
 *	------------------------------ LIST FUNCTIONS ------------------------------
*/

t_room			*find_room(t_room *rooms, char *name);

#endif

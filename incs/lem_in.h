/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 15:49:58 by femaury           #+#    #+#             */
/*   Updated: 2018/06/19 14:58:09 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

/*
**	----------------------------- SYSTEM LIBRARIES -----------------------------
*/

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <stdio.h>
# include <limits.h>

/*
**	------------------------------- MY LIBRARIES -------------------------------
*/

# include "../libs/libft/incs/libft.h"
# include "../libs/libft/incs/get_next_line.h"
# include "../libs/printf/incs/libftprintf.h"

/*
**	------------------------------ STATUS DEFINES ------------------------------
*/

# define EMPTY 0
# define OCCUPIED 1
# define START 2
# define END 3

/*
**	------------------------------- ERROR DEFINES ------------------------------
*/

# define E_MALLOC -1
# define E_SPLIT -2
# define E_NOPOP -3
# define E_ROOM -4
# define E_LINK -5
# define E_LINK1 -6
# define E_LINK2 -7
# define E_NOPATH -8
# define E_NOSTART -9
# define E_NOEND -10

/*
**	-------------------------------- STRUCTURES --------------------------------
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
	struct s_room	*best;
	struct s_room	*next;
}				t_room;

typedef struct	s_env
{
	int				error;
	char			*file;
	char			*start;
	char			*end;
	char			*del;
	unsigned int	pop;
	unsigned int	best_len;
	t_list			*best;
	t_room			*best_room;
	t_list			*tmp;
	t_ant			*ants;
	t_room			*rooms;
}				t_env;

/*
**	----------------------------- LEM_IN FUNCTIONS -----------------------------
*/

void			parse_input(t_env *env);
void			find_best_path(t_env *env);
void			send_ants(t_env *env);
void			lem_in_exit(int error);

/*
**	------------------------------ LIST FUNCTIONS ------------------------------
*/

t_room			*add_room(t_env *env, char *line, int status);
t_room			*find_room(t_room *rooms, char *name);
void			env_init(t_env *env);
void			ant_del(t_ant **ants);
void			room_del(t_room **rooms);
void			link_best_room(t_env *env);

#endif

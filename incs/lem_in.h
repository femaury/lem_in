/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 15:49:58 by femaury           #+#    #+#             */
/*   Updated: 2018/06/09 19:57:24 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <stdio.h>

# include "../libs/libft/incs/libft.h"
# include "../libs/printf/incs/libftprintf.h"

# define EMPTY 0
# define OCCUPIED 1
# define START 2
# define END 3

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
	unsigned int	pop;
	struct s_ant	*ants;
	struct s_room	*rooms;
}				t_env;

void			parse_input(t_env *env);
void			lem_in_exit(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_structfuncs_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 11:37:30 by femaury           #+#    #+#             */
/*   Updated: 2018/06/19 11:47:52 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** 		void	set_info(t_env *env, t_room *new, char *line);
**
**	Extension of add_room. Splits the line to get info for the name
**	and coordinates of the room.
*/

static int	set_info(t_env	*env, t_room *new, char *line)
{
	unsigned int	i;
	unsigned int	size;
	char			**info;

	i = 0;
	if (!(info = ft_strsplit(line, ' ')))
		lem_in_exit(E_SPLIT);
	if (!info[0] || !info[1] || !info[2])
		return (1);
	size = ft_strtabsize(info);
	new->name = NULL;
	while (i < size - 2)
	{
		env->del = new->name;
		new->name = ft_strjoin_split(new->name, info[i++], ' ');
		ft_strdel(&env->del);
	}
	new->posx = ft_atoi(info[size - 2]);
	new->posy = ft_atoi(info[size - 1]);
	ft_tabdel((void **)info, size);
	return (0);
}

/*
** 		t_room	*add_room(t_env *env, char *line, int status);
**
**	Mallocs new list item and adds to it the room's name, status,
**	coordinates, ant ID and sets its pointers to NULL.
*/

t_room		*add_room(t_env *env, char *line, int status)
{
	t_room			*new;

	if (!(new = (t_room *)malloc(sizeof(t_room))))
		lem_in_exit(E_MALLOC);
	if (set_info(env, new, line))
		return (NULL);
	new->status = status;
	new->ant_id = 0;
	new->links = NULL;
	new->next = NULL;
	new->best = NULL;
	return (new);
}

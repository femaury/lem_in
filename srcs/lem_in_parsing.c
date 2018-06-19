/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:18:41 by femaury           #+#    #+#             */
/*   Updated: 2018/06/19 11:44:43 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** 		void	create_colony(t_env *env);
**
**	Creates the linked list containing all the ants.
**	Makes env->ants point to tat list. Gives each ant
**	an ID (from 1 to N) and sets their pointers to NULL.
*/

static void		create_colony(t_env *env, char *line)
{
	t_ant			*new;
	unsigned int	i;

	i = 2;
	env->pop = ft_atoi(line);
	if (env->pop <= 0)
		lem_in_exit(E_NOPOP);
	if (!(new = (t_ant *)malloc(sizeof(t_ant))))
		lem_in_exit(E_MALLOC);
	new->id = 1;
	new->next = NULL;
	new->room = NULL;
	env->ants = new;
	while (i <= env->pop)
	{
		if (!(new->next = (t_ant *)malloc(sizeof(t_ant))))
			lem_in_exit(E_MALLOC);
		new = new->next;
		new->id = i;
		new->next = NULL;
		new->room = NULL;
		i++;
	}
}

/*
** 		t_room	*add_room(char *line, int status);
**
**	Mallocs new list item and adds to it the room's name,
**	status, coordinates, ant ID and sets its pointers to
**	NULL.


static t_room	*add_room(t_env *env, char *line, int status)
{
	unsigned int	i;
	unsigned int	size;
	char			**info;
	t_room			*new;

	i = 0;
	if (!(new = (t_room *)malloc(sizeof(t_room))))
		lem_in_exit(E_MALLOC);
	if (!(info = ft_strsplit(line, ' ')))
		lem_in_exit(E_SPLIT);
	if (!info[0] || !info[1] || !info[2])
		return (NULL);
	size = ft_strtabsize(info);
	new->name = NULL;
	while (i < size - 2)
	{
		env->del = new->name;
		new->name = ft_strjoin_split(new->name, info[i++], ' ');
		ft_strdel(&env->del);
	}
	new->status = status;
	new->posx = ft_atoi(info[size - 2]);
	new->posy = ft_atoi(info[size - 1]);
	new->ant_id = 0;
	new->links = NULL;
	new->next = NULL;
	new->best = NULL;
	ft_tabdel((void **)info, size);
	return (new);
}
*/
/*
** 		void	build_anthill(t_env *env, char *line, int *status);
**
**	Either creates or adds to env->rooms by calling add_room. Resets status.
*/

static int		build_anthill(t_env *env, char *line, int *status)
{
	static t_room	*curr;

	if (!env->pop)
		lem_in_exit(E_NOPOP);
	if (!env->rooms)
	{
		curr = add_room(env, line, *status);
		env->rooms = curr;
	}
	else
	{
		curr->next = add_room(env, line, *status);
		curr = curr->next;
	}
	if (!curr)
		return (env->error = E_ROOM);
	if (*status == START)
		env->start = curr->name;
	else if (*status == END)
		env->end = curr->name;
	*status = 0;
	return (0);
}

/*
** 		void	set_links(t_env *env, char *line);
**
**	For each tunnel declaration, finds the two concerned
**	rooms and creates or adds to their links t_list with
**	the name of the other room. Exits if tunnel declaration
**	is invalid. (e.g. more or less than two rooms or
**	invalid room name)
*/

static int		set_links(t_env *env, char *line)
{
	t_room	*curr;
	char	**names;

	if (!(names = ft_strsplit(line, '-')))
		lem_in_exit(E_SPLIT);
	if (!names[0] || !names[1])
		return (env->error = E_LINK);
	if (!find_room(env->rooms, names[1]))
		return (env->error = E_LINK2);
	if (!(curr = find_room(env->rooms, names[0])))
		return (env->error = E_LINK1);
	if (!curr->links)
		curr->links = ft_lstnew(names[1], ft_strlen(names[1]) + 1);
	else
		ft_lstprepend(&curr->links, ft_lstnew(names[1],
					ft_strlen(names[1]) + 1));
	curr = find_room(env->rooms, names[1]);
	if (!curr->links)
		curr->links = ft_lstnew(names[0], ft_strlen(names[0]) + 1);
	else
		ft_lstprepend(&curr->links, ft_lstnew(names[0],
					ft_strlen(names[0]) + 1));
	ft_tabdel((void **)names, ft_strtabsize(names));
	return (0);
}

/*
** 		void	parse_input(t_env *env);
**
**	Start function parsing stdin. Loops on GNL.
**	First number found is considered to be the
**	ant population. All comments are ignored.
**	Only "start" and "end" commands are taken
**	into account. All lines containing ' ' are
**	considered as room declarations and all
**	lines containing '-' as tunnel declarations.
*/

void			parse_input(t_env *env)
{
	int		status;
	char	*line;

	status = 0;
	while (!(line = NULL) && !env->error && ft_gnl(0, &line) > 0 && line)
	{
		if (line[0] != '#' || line[1] == '#')
		{
			if (!env->pop && ft_strisdigit(line) && !(status = 0))
				create_colony(env, line);
			else if (!ft_strncmp(line, "##start", 7))
				status = START;
			else if (!ft_strncmp(line, "##end", 5))
				status = END;
			else if (ft_strhasc(line, '-') && !ft_strhasc(line, ' '))
				set_links(env, line);
			else if (ft_strhasc(line, ' '))
				build_anthill(env, line, &status);
		}
		env->del = env->file;
		env->file = ft_strjoin_split(env->file, line, '\n');
		ft_strdel(&env->del);
		ft_strdel(&line);
	}
}

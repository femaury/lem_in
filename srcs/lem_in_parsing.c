/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:18:41 by femaury           #+#    #+#             */
/*   Updated: 2018/06/10 12:49:22 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
 * 		void	create_colony(t_env *env);
 *
 *	Creates the linked list containing all the ants.
 *	Makes env->ants point to tat list. Gives each ant
 *	an ID (from 1 to N) and sets their pointers to NULL.
 *
*/

static void		create_colony(t_env *env)
{
	t_ant			*new;
	unsigned int	i;

	i = 2;
	if (!env->pop)
		lem_in_exit();
	if (!(new = (t_ant *)malloc(sizeof(t_ant))))
		lem_in_exit();
	new->id = 1;
	new->next = NULL;
	new->room = NULL;
	env->ants = new;
	while (i <= env->pop)
	{
		if (!(new->next = (t_ant *)malloc(sizeof(t_ant))))
			lem_in_exit();
		new = new->next;
		new->id = i;
		new->next = NULL;
		new->room = NULL;
		i++;
	}
}

/*
 * 		t_room	*add_room(char *line, int status);
 *
 *	Mallocs new list item and adds to it the room's name,
 *	status, coordinates, ant ID and sets its pointers to
 *	NULL.
 *
*/

static t_room	*add_room(char *line, int status)
{
	char		**info;
	t_room		*new;

	if (!(new = (t_room *)malloc(sizeof(t_room))))
		lem_in_exit();
	info = ft_strsplit(line, ' ');
	if (!info[0] || !info[1] || !info[2])
		lem_in_exit();
	new->name = ft_strdup(info[0]);
	new->status = status;
	new->posx = ft_atoi(info[1]);
	new->posy = ft_atoi(info[2]);
	new->ant_id = 0;
	new->links = NULL;
	new->next = NULL;
	ft_tabdel((void **)info, ft_strtabsize(info));
	return (new);
}

/*
 * 		void	build_anthill(t_env *env, char *line, int *status);
 *
 *	Either creates or adds to env->rooms by calling add_room. Resets status.
 *
*/

static void		build_anthill(t_env *env, char *line, int *status)
{
	static t_room	*curr;

	if (!env->rooms)
	{
		curr = add_room(line, *status);
		env->rooms = curr;
	}
	else
	{
		curr->next = add_room(line, *status);
		curr = curr->next;
	}
	*status = 0;
}

/*
 * 		t_room	*find_room(t_room *rooms, char *name);
 *
 *	  Finds room in linked list with corresponding name.
 *	  If no room is found, returns NULL so that a call to
 *	  lem_in_exit can be made from parent function.
 *
*/

static t_room	*find_room(t_room *rooms, char *name)
{
	t_room	*curr;

	curr = rooms;
	while (curr)
	{
		if (!ft_strcmp(curr->name, name))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

/*
 * 		void	set_links(t_env *env, char *line);
 *
 *	For each tunnel declaration, finds the two concerned
 *	rooms and creates or adds to their links t_list with
 *	the name of the other room. Exits if tunnel declaration
 *	is invalid. (e.g. more or less than two rooms or
 *	invalid room name)
 *
*/

static void		set_links(t_env *env, char *line)
{
	t_room	*curr;
	char	**names;

	names = ft_strsplit(line, '-');
	if (!names[0] || !names[1])
		lem_in_exit();
	if (!(curr = find_room(env->rooms, names[0])))
		lem_in_exit();
	if (!curr->links)
		curr->links = ft_lstnew(names[1], ft_strlen(names[1]));
	else
		ft_lstadd(&curr->links, ft_lstnew(names[1], ft_strlen(names[1])));
	if (!(curr = find_room(env->rooms, names[1])))
		lem_in_exit();
	if (!curr->links)
		curr->links = ft_lstnew(names[0], ft_strlen(names[0]));
	else
		ft_lstadd(&curr->links, ft_lstnew(names[0], ft_strlen(names[0])));
	ft_tabdel((void **)names, ft_strtabsize(names));
}

/*
 * 		void	parse_input(t_env *env);
 *
 *	Main function parsing stdout. Loops on GNL.
 *	First number found is considered to be the
 *	ant population. All comments are ignored.
 *	Only "start" and "end" commands are taken
 *	into account. All lines containing ' ' are
 *	considered as room declarations and all
 *	lines containing '-' as tunnel declarations.
 *
*/

void			parse_input(t_env *env)
{
	int		status;
	char	*line;

	while (!(line = NULL) && ft_gnl(0, &line) > 0 && line)
	{
		if (line[0] != '#' || line[1] == '#')
		{
			if (!env->pop && ft_isdigit(line[0]))
			{
				env->pop = ft_atoi(line);
				create_colony(env);
			}
			else if (!ft_strncmp(line, "##start", 7))
				status = START;
			else if (!ft_strncmp(line, "##end", 5))
				status = END;
			else if (ft_strhasc(line, ' '))
				build_anthill(env, line, &status);
			else if (ft_strhasc(line, '-'))
				set_links(env, line);
		}
		ft_strdel(&line);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:18:41 by femaury           #+#    #+#             */
/*   Updated: 2018/06/09 19:09:26 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

static t_room	*add_room(char *line)
{
	char		**info;
	int			status;
	t_room		*new;

	if (!(new = (t_room *)malloc(sizeof(t_room))))
		lem_in_exit();
	if (!(status = 0) && line[0] == '#')
	{
		if (!ft_strncmp(line, "##start", 7))
			status = START;
		else if (!ft_strncmp(line, "##end", 5))
			status = END;
		ft_strdel(&line);
		if (ft_gnl(0, &line) < 1 || !line)
			lem_in_exit();
	}
	info = ft_strsplit(line, ' ');
	if (!info[0] || !info[1] || !info[2])
		lem_in_exit();
	new->name = ft_strdup(info[0]);
	new->status = status;
	new->posx = ft_atoi(info[1]);
	new->posy = ft_atoi(info[2]);
	new->ant_id = 0;
	new->next = NULL;
	ft_tabdel((void **)info, ft_strtabsize(info));
	return (new);
}

static void		build_anthill(t_env *env, char *line)
{
	static t_room	*curr;

	if (!env->rooms)
	{
		curr = add_room(line);
		env->rooms = curr;
	}
	else
	{
		curr->next = add_room(line);
		curr = curr->next;
	}
}

void			parse_input(t_env *env)
{
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
			else if (line[1] == '#' || ft_strhasc(line, ' '))
				build_anthill(env, line);
		}
		ft_strdel(&line);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:01:27 by femaury           #+#    #+#             */
/*   Updated: 2018/04/21 15:21:45 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	if ((!s1[i] && s2[i]) || (s1[i] && !s2[i]))
		return (0);
	while ((s1[i] == s2[i]) && (s1[i] || s2[i]))
		i++;
	return (s1[i] - s2[i]) == 0 ? 1 : 0;
}
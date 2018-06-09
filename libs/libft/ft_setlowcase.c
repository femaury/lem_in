/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 20:14:05 by femaury           #+#    #+#             */
/*   Updated: 2018/05/12 21:24:58 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_setlowcase(char *s)
{
	while (*s)
	{
		if (ft_isupper(*s))
			*s += 32;
		s++;
	}
}

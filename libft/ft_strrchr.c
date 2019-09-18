/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:08:19 by fsinged           #+#    #+#             */
/*   Updated: 2019/04/15 16:26:57 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *save;

	save = (0);
	while (*s)
	{
		if (*s == (char)c)
			save = (char*)s;
		s++;
	}
	if (save)
		return (save);
	if ((char)c == '\0')
		return ((char*)s);
	return (0);
}

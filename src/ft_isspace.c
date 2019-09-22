/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:49:22 by dtimeon           #+#    #+#             */
/*   Updated: 2019/04/28 16:21:52 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || \
		c == ' ')
		return (1);
	return (0);
}

/*
** NAME
**      isspace -- white-space character test
**
** LIBRARY
**      Standard C Library (libc, -lc)
**
** SYNOPSIS
**      #include <ctype.h>
**
**      int	isspace(int c);
**
** DESCRIPTION
**      The isspace() function tests for the white-space characters.  For any
** 	 locale, this includes the following standard characters:
**
**      ``\t''   ``\n''    ``\v''    ``\f''    ``\r''    `` ''
**
**      In the "C" locale, isspace() successful test is limited to these
** 	 characters only.  The value of the argument must be representable as
** 	 an unsigned char or the value of EOF.
**
** RETURN VALUES
**      The isspace() function returns zero if the character tests false and
** 	 returns non-zero if the character tests true.
*/

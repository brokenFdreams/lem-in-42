/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:17:18 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/01 16:26:29 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <limits.h>

static int				has_hex_preffix(const char *p)
{
	if (*p == '0' && ((*(p + 1) == 'x') || (*(p + 1) == 'X')))
		return (1);
	return (0);
}

static int				has_oct_preffix(const char **ptr)
{
	if (**ptr == '0')
	{
		return (1);
	}
	return (0);
}

static int				is_base_digit(char c, int base)
{
	char				*digits;

	digits = "0123456789abcdefghijklmnopqrstuvwxyz";
	if (ft_strnchr(digits, ft_tolower(c), (size_t)base))
		return (1);
	return (0);
}

static int				check_the_base(const char *nptr, int base)
{
	if (base != 0)
		return (base);
	if (has_hex_preffix(nptr))
		return (16);
	else if (has_oct_preffix(&nptr))
		return (8);
	else
		return (10);
}

long int				ft_strtol(const char *nptr, char **endptr, int base)
{
	int					sign;
	unsigned long int	result;
	unsigned long int	limit;

	sign = 1;
	result = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *(nptr) == '+')
		sign = (*(nptr++) == '-') ? -1 : 1;
	base = check_the_base(nptr, base);
	nptr = (base == 16) ? nptr + 2 : nptr;
	limit = (sign > 0) ? LONG_MAX : (size_t)LONG_MAX + 1;
	while (is_base_digit(*nptr, base))
	{
		if ((((result * base + ft_chrtoint(*nptr)) / base) == result) &&
				(result * base + ft_chrtoint(*nptr)) < limit)
			result = result * base + ft_chrtoint(*nptr);
		else
			result = limit;
		nptr++;
	}
	if (endptr)
		*endptr = (char *)nptr;
	return ((long int)result * sign);
}

/*
** SYNOPSIS
**       #include <stdlib.h>
**
**       long int strtol(const char *nptr, char **endptr, int base);
**
**       long long int strtoll(const char *nptr, char **endptr, int base);
**
** DESCRIPTION
**       The strtol() function converts the initial part of the string in
**       nptr to a long integer value according to the given base,  which
**       must be between 2 and 36 inclusive, or be the special value 0.
**
**       The string may begin with an arbitrary amount of white space (as
**       determined by isspace(3)) followed by a single optional  '+'  or
**       '-'  sign.  If base is zero or 16, the string may then include a
**       "0x" prefix, and the number will be read in base 16;  otherwise,
**       a  zero  base is taken as 10 (decimal) unless the next character
**       is '0', in which case it is taken as 8 (octal).
**
**       The remainder of the string is converted to a long int value  in
**       the obvious manner, stopping at the first character which is not
**       a valid digit in the given base.  (In bases above 10, the letter
**       'A'  in  either uppercase or lowercase represents 10, 'B' repre‐
**       sents 11, and so forth, with 'Z' representing 35.)
**
**       If endptr is not NULL, strtol() stores the address of the  first
**       invalid  character  in *endptr.  If there were no digits at all,
**       strtol() stores the original  value  of  nptr  in  *endptr  (and
**       returns 0).  In particular, if *nptr is not '\0' but **endptr is
**       '\0' on return, the entire string is valid.
**
**       The strtoll() function works just like the strtol() function but
**       returns a long long integer value.
**
** RETURN VALUE
**       The  strtol()  function  returns  the  result of the conversion,
**       unless the value would underflow or overflow.  If  an  underflow
**       occurs,  strtol() returns LONG_MIN.  If an overflow occurs, str‐
**       tol() returns LONG_MAX.  In both cases, errno is set to  ERANGE.
**       Precisely  the  same  holds  for  strtoll()  (with LLONG_MIN and
**       LLONG_MAX instead of LONG_MIN and LONG_MAX).
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:59:24 by fsinged           #+#    #+#             */
/*   Updated: 2019/04/15 14:22:49 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	i;
	size_t	res;

	i = 0;
	dstlen = ft_strlen(dst);
	res = ft_strlen(src);
	if (dstlen + 1 > size)
		return (res + size);
	else
		res += dstlen;
	while (i < size - dstlen - 1 && src[i] != '\0')
	{
		dst[i + dstlen] = src[i];
		i++;
	}
	dst[i + dstlen] = '\0';
	return (res);
}

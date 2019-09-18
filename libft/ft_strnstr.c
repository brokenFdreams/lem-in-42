/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:17:03 by fsinged           #+#    #+#             */
/*   Updated: 2019/04/05 16:58:40 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	if (!*needle)
		return ((char*)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (haystack[i] && needle[j] &&
					haystack[i] == needle[j] && i < len)
			{
				i++;
				j++;
			}
		}
		i = i - j;
		if (!needle[j])
			return ((char*)(haystack + i));
		i++;
	}
	return (NULL);
}

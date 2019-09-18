/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:10:27 by fsinged           #+#    #+#             */
/*   Updated: 2019/04/09 16:58:50 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t i;
	size_t j;

	if (!*needle)
		return ((char*)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (needle[j] && haystack[i] && needle[j] == haystack[i])
			{
				j++;
				i++;
			}
		}
		i = i - j;
		if (!needle[j])
			return ((char*)(haystack + i));
		i++;
	}
	return (NULL);
}

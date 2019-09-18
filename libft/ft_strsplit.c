/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 13:57:16 by fsinged           #+#    #+#             */
/*   Updated: 2019/04/16 12:37:55 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t count;
	size_t i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			|| (s[i] != c && i == 0))
			count++;
		i++;
	}
	return (count);
}

static char		**ft_split(char const *s, char c, char **str, size_t len)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i - 1] == c) || (i == 0 && s[i] != c))
		{
			j = 0;
			while (s[i + j] != c && s[i + j])
				j++;
			str[k] = ft_strsub(s, i, j);
			if (str[k] == NULL)
				free(str[k]);
			k++;
			i = i + j;
		}
		if (s[i] != '\0')
			i++;
	}
	str[len] = NULL;
	return (str);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_count_words(s, c);
	str = (char**)malloc(sizeof(char*) * (len + 1));
	if (str == NULL)
		return (NULL);
	return (ft_split(s, c, str, len));
}

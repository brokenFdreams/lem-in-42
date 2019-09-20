/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 11:58:30 by fsinged           #+#    #+#             */
/*   Updated: 2019/09/20 12:37:18 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Check str, room is it or not
*/

int		isroom(char *str)
{
	if (*str == 'L' || *str == '#')
		return (0);
	while (*str && *str != ' ')
		str++;
	if (*str == '\0')
		return (0);
	str++;
	while (*str && *str != ' ')
		if (!ft_isdigit(*str))
			return (0);
		else
			str++;
	if (*str == '\0')
		return (0);
	str++;
	while (*str && *str != '\n')
		if (!ft_isdigit(*str))
			return (0);
		else
			str++;
	return (1);
}

/*
** Check str, way is it or not
*/

int		isway(char *str)
{
	if (*str == 'L' || *str == '#')
		return (0);
	while (*str && *str != '-')
		str++;
	if (*str == '\0')
		return (0);
	str++;
	while (*str && *str != '\n')
		str++;
	return (1);
}

/*
** Fill rooms
*/

int		fill_rooms(char **data, char ***rooms, int size)
{
	int i;
	int j;

	i = 0;
	j = 1;
	*rooms = (char**)malloc(sizeof(char*) * (size + 1));
	while (++i && data[i] && j < size)
		if (ft_strcmp(data[i], "##start") == 0)
			*rooms[0] = ft_strdup(data[++i]);
		else if (ft_strcmp(data[i], "##end") == 0 && size--)
			*rooms[size] = ft_strdup(data[++i]);
		else if (isroom(data[i]))
			*rooms[j++] = ft_strdup(data[i]);
	*rooms[size + 1] = NULL;
	return (i);
}

/*
** Fill ways
*/

void	fill_ways(char **data, char ***ways, int size)
{
	int i;
	int j;

	i = 0;
	j = 0;
	*ways = (char**)malloc(sizeof(char*) * (size + 1));
	while (data[i] && j < size)
	{
		if (isway(data[i]))
			ways[j++] = ft_strdup(data[i]);
		i++;
	}
	ways[j] = NULL;
}

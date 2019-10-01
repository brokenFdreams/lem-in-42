/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 11:58:30 by fsinged           #+#    #+#             */
/*   Updated: 2019/09/26 14:21:25 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Check str, room is it or not
*/

int		isroom(char *str)
{
	if (!*str || *str == 'L' || *str == '#')
		return (0);
	while (*str && *str != ' ')
		str++;
	if (!*str)
		return (0);
	str++;
	while (*str && *str != ' ')
		if (!ft_isdigit(*str))
			return (0);
		else
			str++;
	if (!*str)
		return (0);
	str++;
	if (!*str)
		return (0);
	while (*str)
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
	if (*str == '\0')
		return (0);
	return (1);
}

/*
** Fill rooms
*/

int		fill_rooms(char **data, char ***rooms, int size)
{
	int i;
	int j;
	int flag;

	i = 0;
	j = 1;
	flag = 0;
	if (size < 2)
		ft_error("No rooms");
	*rooms = (char**)malloc(sizeof(char*) * (size + 1));
	while (data[++i] && ((j < size && flag != 2) || (flag == 2 && j < size - 1)))
		if (ft_strcmp(data[i], "##start") == 0 && ++flag)
			(*rooms)[0] = ft_strdup(data[++i]);
		else if (ft_strcmp(data[i], "##end") == 0 && ++flag)
			(*rooms)[size - 1] = ft_strdup(data[++i]);
		else if (isroom(data[i]))
			(*rooms)[j++] = ft_strdup(data[i]);
	if (flag != 2)
		ft_error("No mandatory comments\n");
	(*rooms)[size] = NULL;
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
	if (size < 1)
		ft_error("No possible solution\n");
	*ways = (char**)malloc(sizeof(char*) * (size + 1));
	while (data[i] && j < size)
	{
		if (isway(data[i]))
			(*ways)[j++] = ft_strdup(data[i]);
		i++;
	}
	(*ways)[j] = NULL;
}

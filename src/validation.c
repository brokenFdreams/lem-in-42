/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:44:07 by fsinged           #+#    #+#             */
/*   Updated: 2019/09/19 16:24:12 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Check fisrt str in file
*/

static int	read_num(char *str)
{
	int num;

	num = ft_atoi(str);
	while (*str)
	{
		if (!ft_isdigit(*str))
			ft_error("Error");
		str++;
	}
	return (num);
}

/*
** Check str, room is it or not
*/

static int	isroom(char *str)
{
	if (*str == 'L' || *str == '#')
		return (0);
	while (*str && *str != ' ')
		str++;
	str++;
	while (*str && *str != ' ')
		if (!ft_isdigit(*str))
			return (0);
		else
			str++;
	str++;
	while (*str && *str != '\n')
		if (!ft_isdigit(*str))
			return (0);
		else
			str++;
	return (1);
}

/*
** Count the number of rooms
*/

static int	count_rooms(char **data)
{
	int count;
	int i;

	count = 0;
	i = -1;
	while (data[++i])
		if (isroom(data[i]))
			count++;
	return (count);
}

int			validation(char **data, char ***rooms, char ***ways)
{
	int	ants;
	int i;
	int rcount;
	int wcount;

	i = 0;
	rcount = 0;
	wcount = 0;
	while (data[i][0] == '#' && data[i][1] != '#')
		i++;
	ants = read_num(data[i]);
	while (++i && data[i])
		if (!(ft_strcmp(data[i],  "##start") == 0 ||
			ft_strcmp(data[i], "##end") == 0 ||
			(data[i][0] == '#' && data[i][1] != '#')))
		{
			if (isroom(data[i]))
				rcount++;
			else if (isway)
				wcount++;
			else
				break ;
		}
	fill_ways(data + fill_rooms(data, rooms, rcount), ways, wcount);
	return (ants);
}

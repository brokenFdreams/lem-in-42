/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:44:07 by fsinged           #+#    #+#             */
/*   Updated: 2019/09/24 14:32:31 by fsinged          ###   ########.fr       */
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
	if (num < 1)
		ft_error("No ants\n");
	while (*str)
	{
		if (!ft_isdigit(*str))
			ft_error("Error\n");
		str++;
	}
	return (num);
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
	while (data[i] && data[i][0] == '#' && data[i][1] != '#')
		i++;
	ants = read_num(data[i]);
	while (++i && data[i])
		if ((ft_strcmp(data[i], "##start") == 0 ||
			ft_strcmp(data[i], "##end") == 0) && !isroom(data[i + 1]))
			ft_error("No start/end\n");
		else if (!(ft_strcmp(data[i], "##start") == 0 ||
			ft_strcmp(data[i], "##end") == 0 ||
			(data[i][0] == '#' && data[i][1] != '#')))
		{
			if (isroom(data[i]))
				rcount++;
			else if (isway(data[i]))
				wcount++;
			else
				break ;
		}
	if (data[i] && data[i][0] == '#' && data[i][1] == '#')
		ft_error("Invalid comment\n");
	fill_rooms(data, rooms, rcount);
	fill_ways(data, ways, wcount);
	return (ants);
}

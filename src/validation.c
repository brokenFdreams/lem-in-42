/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:44:07 by fsinged           #+#    #+#             */
/*   Updated: 2019/09/19 15:04:22 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Check fisrt str in file
*/

static int	read_ants(char *str)
{
	int ants;

	ants = ft_atoi(str);
	while (*str)
	{
		if (!ft_isdigit(*str))
			ft_error("Error");
		str++;
	}
	return (ants);
}

int			validation(char **data)
{
	int error;
	int	ants;
	int i;

	i = 0;
	while (data[i][0] == '#' && data[i][1] != '#')
		i++;
	ants = read_ants(data[i]);
	while (data[i])
	{
		if (ft_strcmp(data[i],  "##start") == 0 ||
			ft_strcmp(data[i], "##end") == 0 ||
			(data[i][0] == '#' && data[i][1] != '#') ||
			
		i++;
	}

	return (ants);
}

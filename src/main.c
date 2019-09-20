/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:30:35 by fsinged           #+#    #+#             */
/*   Updated: 2019/09/20 12:42:48 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** free two-dimensional array
*/

static void	ft_strddel(char **data)
{
	int i;

	i = 0;
	while (data[i] != NULL)
	{
		free(data[i]);
		i++;
	}
	free(data);
}

/*
** The first: checks the number of arguments
** The second: read data from file
** The third: validation of data
** The fifth: overwrite data in usable way
** The sixth: algorithm
*/

int		main(int argc, char **argv)
{
	char	**data;
	char	**rooms;
	char	**ways;
	//list

	if (argc != 2)
		ft_error();
	read_data(argv[1], &data);
	validation(data, &rooms, &ways);
	ft_strddel(data);
	overwrite(rooms, ways);
	ft_strddel(rooms);
	ft_strddel(ways);
	
//	ft_free_list
	return (0);
}

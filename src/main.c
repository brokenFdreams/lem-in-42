/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:30:35 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/04 14:07:06 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print(char **data)
{
	while (*data != NULL)
	{
		printf("%s\n", *data);
		data++;
	}
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
	int		ants;

	//list
	if (argc != 2)
		ft_error("Error\n");
	read_data(argv[1], &data);
	ants = validation(data, &rooms, &ways);
	ft_free_strings_array(&data);

	ft_free_strings_array(&rooms);
	ft_free_strings_array(&ways);
//	ft_free_list
	return (0);
}

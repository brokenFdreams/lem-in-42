/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:30:35 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/21 16:05:37 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print(char **data)
{
	while (*data != NULL)
	{
		write(1, *data, ft_strlen(*data));
		write(1, "\n", 1);
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
	t_options *options;

	//list
	if (argc > 1)
		options = read_options(argc - 1, argv + 1);
	read_data(&data);
	ants = validation(data, &rooms, &ways);
	ft_free_strings_array(&data);

	ft_free_strings_array(&rooms);
	ft_free_strings_array(&ways);
	if (options)
		free(options);
//	ft_free_list
	return (0);
}

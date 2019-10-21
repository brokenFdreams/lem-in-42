/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:07:48 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/21 15:10:46 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_options		*init_options()
{
	t_options	*options;

	options = malloc(sizeof(t_options));
	options->path = 0;
	options->color = 0;
	options->stat = 0;
	options->help = 0;
	options->log = 0;
	return (options);
}

t_options		*read_options(int argc, char **argv)
{
	t_options	*options;
	int			i;

	options = init_options();
	while (--argc > 0)
		if (argv[argc][0] == '-' && argv[argc][1] == '-')
		{
			if (ft_strequ(argv[argc], "--path"))
				options->path = 1;
			else if (ft_strequ(argv[argc], "--color"))
				options->color = 1;
			else if (ft_strequ(argv[argc], "--stat"))
				options->stat = 1;
			else if (ft_strequ(argv[argc], "--help"))
				options->help = 1;
			else if (ft_strequ(argv[argc], "--log"))
				options->log = 1;
		}
		else if (argv[argc][0] == '-' && !(i = 0))
		{
			while (argv[argc][++i])
				if (argv[argc][i] == 'p')
					options->path = 1;
				else if (argv[argc][i] == 'c')
					options->color = 1;
				else if (argv[argc][i] == 's')
					options->stat = 1;
				else if (argv[argc][i] == 'h')
					options->help = 1;
				else if (argv[argc][i] == 'l')
					options->log = 1;
		}
	return (options);
}

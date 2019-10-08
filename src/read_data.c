/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:21:33 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/08 14:57:11 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Count strs in file
*/

static int	count_str(char *arg)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(arg, O_RDONLY);
	count = 0;
	while (get_next_line(fd, &line) > 0 && ++count)
		ft_strdel(&line);
	close(fd);
	return (count);
}

/*
** Reading data from file
** if there's no file, then call ft_error
*/

void		read_data()
{
	int		count;
	int		gnl;
	char	*line;

	count = count_str(arg);
	if (count == 0)
		ft_error("Empty map\n");
	*data = (char**)malloc(sizeof(char*) * (count + 1));
	count = 0;
	while ((gnl = get_next_line(0, &line)) > 0)
		(*data)[count++] = line;
	if (gnl == -1)
		ft_error("Usage: ./lem-in < [file.map]");
	(*data)[count] = NULL;
}

t_options	*init_options()
{
	t_options	*options;

	options = malloc(sizeof(t_options));
	options->path = 0;
	options->color = 0;
	options->stat = 0;
	options->help = 0;
	options->log = 0;
}

t_options	*read_options(int argc, char **argv)
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

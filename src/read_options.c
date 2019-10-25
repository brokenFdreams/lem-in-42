/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:15:44 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 15:57:30 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	save_full_option(char *line, t_options *options)
{
	if (ft_strequ(line, "path"))
		options->path = 1;
	else if (ft_strequ(line, "color"))
		options->color = 1;
	else if (ft_strequ(line, "stat"))
		options->stat = 1;
	else if (ft_strequ(line, "log"))
		options->log = 1;
	else if (ft_strequ(line, "save_map"))
		options->save_map = 1;
	else if (ft_strequ(line, "quiet"))
		options->quiet = 1;
	else if (ft_strequ(line, "help"))
		options->help = 1;
	else
		options->usage = 1;
}

static void	save_short_options(char *line, t_options *options)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'p')
			options->path = 1;
		else if (line[i] == 'c')
			options->color = 1;
		else if (line[i] == 's')
			options->stat = 1;
		else if (line[i] == 'h')
			options->help = 1;
		else if (line[i] == 'l')
			options->log = 1;
		else if (line[i] == 'm')
			options->save_map = 1;
		else if (line[i] == 'q')
			options->quiet = 1;
		else
			options->usage = 1;
		i++;
	}
}

void		read_options(int argc, char **argv, t_options *options)
{
	while (--argc >= 0)
		if (argv[argc][0] == '-' && argv[argc][1] == '-')
			save_full_option(argv[argc] + 2, options);
		else if (argv[argc][0] == '-')
			save_short_options(argv[argc] + 1, options);
}

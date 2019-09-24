/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:21:33 by fsinged           #+#    #+#             */
/*   Updated: 2019/09/24 13:22:06 by fsinged          ###   ########.fr       */
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

void		read_data(char *arg, char ***data)
{
	int		count;
	int		gnl;
	int		fd;
	char	*line;

	count = count_str(arg);
	if (count == 0)
		ft_error("Empty map\n");
	fd = open(arg, O_RDONLY);
	*data = (char**)malloc(sizeof(char*) * (count + 1));
	count = 0;
	while ((gnl = get_next_line(fd, &line)) > 0)
		(*data)[count++] = line;
	close(fd);
	if (gnl == -1)
		ft_error("Usage: ./lem-in < [file.map]");
	(*data)[count] = NULL;
}

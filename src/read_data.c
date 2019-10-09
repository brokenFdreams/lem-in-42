/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:21:33 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/09 11:57:13 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_del(t_list **list)
{
	t_list *tmp;
	t_list *buf;

	if (list && *list)
	{
		buf = *list;
		while (buf)
		{
			tmp = buf->next;
			if (buf->content)
				free(buf->content);
			free(buf);
			buf = tmp;
		}
		*list = NULL;
	}
}

void		fill_data(t_list *list, char **data, int size)
{
	int i;

	i = 0;
	data = (char**)malloc(sizeof(char*) * (count + 1));
	while (list)
	{
		data[i++] = ft_strcpy(ft_strnew(list->content_size), list->content);
		list = list->next;
	}
	data[count] = NULL;
}

/*
** Reading data from file
** if there's no file, then call ft_error
*/

void		read_data(char **data)
{
	int		gnl;
	char	*line;
	t_list	*list;
	t_list	*tmp;

	count = 0;
	if ((gnl = get_next_line(0, &line)) > 0 && ++count)
		list = ft_lstnew(line, ft_strlen(line));
	tmp = list->next;
	while ((gnl = get_next_line(0, &line)) > 0 && ++count)
	{
		tmp = ft_lstnew(line, ft_strlen(line));
		tmp = tmp->next;
	}
	if (gnl == -1)
		ft_error("Usage: ./lem-in < [file.map]");
	fill_data(list, data, count);
	ft_del(&list);
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

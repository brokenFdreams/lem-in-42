/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:21:33 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/21 16:01:08 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		del(void *content, size_t size)
{
	if (content)
		ft_memdel(&content);
}

static void	fill_data(t_list *list, char ***data, int size)
{
	int i;

	i = 0;
	*data = (char**)malloc(sizeof(char*) * (size + 1));
	while (i < size)
	{
		(*data)[i++] = ft_strdup(list->content);
		list = list->next;
	}
	(*data)[size] = NULL;
}

/*
** Reading data from file
** if there's no file, then call ft_error
*/

void		read_data(char ***data)
{
	int		gnl;
	char	*line;
	t_list	*list;
	t_list	*tmp;
	size_t	count;

	count = 0;
	if ((gnl = get_next_line(0, &line)) > 0 && ++count)
	{
		list = ft_newlist(&line, ft_strlen(line));
		ft_strdel(&line);
	}
	tmp = list;
	while ((gnl = get_next_line(0, &line)) > 0 && ++count)
	{
		tmp->next = ft_newlist(&line, ft_strlen(line));
		ft_strdel(&line);
		tmp = tmp->next;
	}
	if (gnl == -1)
		ft_error("Usage: ./lem-in < [file.map]");
	fill_data(list, data, count);
	ft_lstdel(&list, &del);
}

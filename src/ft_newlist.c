/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:57:39 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/21 13:29:50 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list		*ft_newlist(char **content, int content_size)
{
	t_list	*list;

	list = (t_list*)malloc(sizeof(t_list));
	if (content == NULL)
	{
		list->content = NULL;
		list->content_size = 0;
	}
	else
	{
		list->content = ft_strcpy(ft_strnew(content_size), *content);
		list->content_size = content_size;
	}
	return (list);
}

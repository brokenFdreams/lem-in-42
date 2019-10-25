/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_links_manipulations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 01:00:12 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 16:39:09 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				del_content(void *content, size_t size)
{
	(void)size;
	free(content);
}

t_list				*copy_links(t_list *links)
{
	t_list			*new;
	t_list			*temp;

	if (!links)
		return (NULL);
	new = ft_lstnew(links->content, sizeof(t_vertex **));
	temp = new;
	while (links->next)
	{
		links = links->next;
		temp->next = ft_lstnew(links->content, sizeof(t_vertex **));
		temp = temp->next;
		if (!temp)
		{
			ft_lstdel(&new, del_content);
			return (NULL);
		}
	}
	temp->next = NULL;
	return (new);
}

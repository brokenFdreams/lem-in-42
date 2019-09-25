/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_removing_impasses.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 21:03:12 by dtimeon           #+#    #+#             */
/*   Updated: 2019/09/25 21:06:22 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ft_lst_del_content(void *content, size_t size)
{
	ft_bzero(content, size);
	ft_memdel(&content);
}

void			remove_impasses(t_vertex *vertex)
{
	t_list		*list;
	t_list		*temp_list;
	t_vertex	*temp_vertex;

	list = vertex->links;
	while (list && list->next)
	{
		temp_list = list->next;
		temp_vertex = *(t_vertex **)temp_list->content;
		if (temp_vertex->dist < 0)
		{
			ft_lstdel(&temp_list, ft_lst_del_content);
			list->next = NULL;
		}
		if (list->next)
			list = list->next;
	}
}

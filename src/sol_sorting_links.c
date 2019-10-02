/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_sorting_links.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:56:30 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/02 16:51:13 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static void			ft_swap(void **a, void **b)
{
	void		*tmp;
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int			compare_vertexes(t_vertex *vertex_a, t_vertex *vertex_b)
{
	if (vertex_a->dist < 0 && vertex_b->dist >= 0)
		return (1);
	else if ((vertex_a->dist > vertex_b->dist) && vertex_b->dist >= 0)
		return (1);
	else if (vertex_a->dist == vertex_b->dist)
	{
		if (vertex_a->links_num > vertex_b->links_num)
			return (1);
		return (0);
	}
	else
		return (0);
}

static t_list		*ft_sort_list(t_list *lst, int (*cmp)(t_vertex *, t_vertex *))
{
	t_list		*tmp;
	t_list		*first;
	
	first = lst;
	while (lst->next)
	{
		tmp = lst->next;
		while (tmp)
		{
			if (cmp(*(t_vertex **)lst->content, *(t_vertex **)tmp->content))
				ft_swap(&lst->content, &tmp->content);
			tmp = tmp->next;
		}
		lst = lst->next;
	}
	return (first);
}

void			sort_links(t_vertex *start)
{
	t_queue		*queue;
	t_vertex	*vertex;
	t_vertex	*temp_vertex;
	t_list		*list;
	
	queue = NULL;
	push(&queue, start);
	while ((vertex = pop(&queue)))
	{
		if (!vertex->is_sorted)
		{
			vertex->links = ft_sort_list(vertex->links, compare_vertexes);
			vertex->is_sorted = 1;
			list = vertex->links;
			while (list)
			{
				temp_vertex = *(t_vertex **)list->content;
				temp_vertex->links_num++;
				if (!temp_vertex->is_sorted)
					push(&queue, temp_vertex);
				list = list->next;
			}
			log_links(STDOUT_FILENO, vertex, "\nAfter links sorting\n");
		}
	}
}

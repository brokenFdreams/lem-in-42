/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_distance_computing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 17:20:11 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/04 21:35:14 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		set_distance(t_vertex *vertex, int dist, char *name)
{
	if (ft_strequ(vertex->path_name, name))
		vertex->dist = INT_MAX;
	else
	{
		if (vertex->dist < 0)
			vertex->dist = dist;
		else
			vertex->dist = ft_min(dist, vertex->dist);
	}
}

// static void		set_distances_by_dfs(t_vertex *vertex, int dist)
// {
// 	t_list		*temp_link;
// 	t_vertex	*temp_vertex;

// 	temp_link = vertex->links;
// 	while (temp_link)
// 	{
// 		temp_vertex = *(t_vertex **)temp_link->content;
// 		set_distance(temp_vertex, dist + 1);
// 		temp_link = temp_link->next;
// 	}
// 	vertex->is_visited = 1;
// 	temp_link = vertex->links;
// 	while (temp_link)
// 	{
// 		temp_vertex = *(t_vertex **)temp_link->content;
// 		if (!temp_vertex->is_start && (temp_vertex != vertex))
// 			set_distances_by_dfs(temp_vertex, temp_vertex->dist);
// 		temp_link = temp_link->next;
// 	}
// }
void			set_distances_by_bfs(t_vertex *end, char *name)
{
	t_queue		*queue;
	t_vertex	*vertex;
	t_vertex	*temp_vertex;
	t_list		*list;
	
	queue = NULL;
	push(&queue, end);
	while ((vertex = pop(&queue)))
	{
		if (!vertex->is_visited)
		{
			vertex->is_visited = 1;
			list = vertex->links;
			while (list)
			{
				vertex->links_num++;
				temp_vertex = *(t_vertex **)list->content;
				set_distance(temp_vertex, vertex->real_dist + 1, name);
				push(&queue, temp_vertex);
				list = list->next;
			}
		}
	}
}


int				compute_distances(t_farm *farm, char *name)
{
	farm->end->dist = 0;
	farm->start->is_visited = 1;
	farm->start->links_num = INT_MAX;
	set_distances_by_bfs(farm->end, name);
	if (farm->start->dist < 0)
		return (0);
	farm->start->dist = INT_MAX;
	return (1);
}
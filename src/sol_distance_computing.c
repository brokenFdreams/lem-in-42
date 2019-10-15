/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_distance_computing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 17:20:11 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/12 20:13:52 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		set_distance(t_vertex *vertex, int dist, char *name)
{
	// if (ft_strequ(vertex->path_name, name))
	// 	vertex->dist = -1;
	// else
	// {
		(void)name;
		if (vertex->dist < 0)
			vertex->dist = dist;
		else
			vertex->dist = ft_min(dist, vertex->dist);
	// }
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
static void		process_vertex(t_vertex *vertex, int dist, char *name,
								t_queue **queue)
{
	set_distance(vertex, dist, name);
	push(queue, vertex);
}

void			set_distances_by_bfs(t_vertex *end, char *name,
									int count_links_flag)
{
	t_queue		*queue;
	t_vertex	*vertex;
	t_vertex	*temp_vertex;
	t_list		*list;
	
	queue = NULL;
	push(&queue, end);
	while ((vertex = pop(&queue)))
	{
		if (!vertex->is_visited && !ft_strequ(vertex->path_name, name))
		{
			vertex->is_visited = 1;
			list = vertex->links;
			while (list)
			{
				if (count_links_flag)
					vertex->links_num++;
				temp_vertex = *(t_vertex **)list->content;
				if (!ft_strequ(temp_vertex->path_name, name))
					process_vertex(temp_vertex, vertex->dist + 1, name, &queue);
				list = list->next;
			}
		}
	}
}

int				compute_distances(t_farm *farm, char *name, int count_links_flag)
{
	farm->end->dist = 0;
	farm->start->is_visited = 1;
	farm->start->links_num = INT_MAX;
	set_distances_by_bfs(farm->end, name, count_links_flag);
	if (farm->start->dist < 0)
		return (0);
	farm->start->dist = INT_MAX;
	return (1);
}

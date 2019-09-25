/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_distance_computing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 17:20:11 by dtimeon           #+#    #+#             */
/*   Updated: 2019/09/25 19:18:09 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		set_distance(t_vertex *vertex, int dist)
{

	if (vertex->dist < 0)
		vertex->dist = dist;
	else
		vertex->dist = ft_min(dist, vertex->dist);
}

static void		set_distances_by_dfs(t_vertex *vertex, int dist)
{
	t_list		*temp_link;
	t_vertex	*temp_vertex;

	temp_link = vertex->links;
	while (temp_link)
	{
		temp_vertex = *(t_vertex **)temp_link->content;
		set_distance(temp_vertex, dist + 1);
		temp_link = temp_link->next;
	}
	vertex->is_visited = 1;
	temp_link = vertex->links;
	while (temp_link)
	{
		temp_vertex = *(t_vertex **)temp_link->content;
		if (!temp_vertex->is_visited && !temp_vertex->is_start)
			set_distances_by_dfs(temp_vertex, temp_vertex->dist);
		temp_link = temp_link->next;
	}
}

int				compute_distances(t_farm *farm)
{
	farm->end->dist = 0;
	set_distances_by_dfs(farm->end, 0);
	if (farm->start->dist < 0)
		return (0);
	return (1);
}
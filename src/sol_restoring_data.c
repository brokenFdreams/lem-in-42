/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_restoring_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:35:14 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 16:56:39 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			set_real_dist(t_vertex **vertexes)
{
	int			i;

	i = 0;
	while (vertexes[i])
	{
		vertexes[i]->real_dist = vertexes[i]->dist;
		i++;
	}
}

void			restore_dist(t_vertex **vertexes)
{
	int			i;

	i = 0;
	while (vertexes[i])
	{
		vertexes[i]->dist = vertexes[i]->real_dist;
		i++;
	}
}

void			clear_combo(t_path_combo **combo, int clr_paths_flag)
{
	int			i;

	(*combo)->starting = NULL;
	(*combo)->paths_num = 0;
	(*combo)->lines_num = INT_MAX;
	(*combo)->num_of_paths_to_use = INT_MAX;
	(void)clr_paths_flag;
	ft_strclr((*combo)->name);
	i = 0;
	while (i < (*combo)->paths_num)
	{
		clear_path((*combo)->paths[i]);
		i++;
	}
}

void			clear_bfs_marks(t_vertex **vertexes, int path_name_clear_flag)
{
	int			i;

	i = 0;
	while (vertexes[i])
	{
		vertexes[i]->dist = -1;
		vertexes[i]->is_visited = 0;
		vertexes[i]->is_sorted = 0;
		if (path_name_clear_flag)
		{
			vertexes[i]->path_num = -1;
			ft_strclr(vertexes[i]->path_name);
			ft_strcpy(vertexes[i]->path_name, "L");
		}
		i++;
	}
}

void			restore_vertexes(t_farm *farm)
{
	t_list		*temp_a;
	t_list		*temp_b;

	temp_a = farm->start->links;
	while (temp_a)
	{
		temp_b = temp_a;
		temp_a = temp_a->next;
		ft_memdel((void **)&temp_b->content);
		ft_memdel((void **)&temp_b);
	}
	farm->start->links = copy_links(farm->original_links_of_start);
	clear_bfs_marks(farm->vertexes, 1);
	restore_dist(farm->vertexes);
	sort_links(farm->start);
}

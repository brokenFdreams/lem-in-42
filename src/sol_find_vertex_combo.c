/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_find_vertex_combo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:34:55 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 15:26:42 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			prepare_for_combo_search(t_path_combo **combo,
											t_vertex *first, t_farm *farm)
{
	if (!*combo)
		*combo = init_path_combo(farm);
	else
		clear_combo(combo, 0);
	ft_strcpy((*combo)->name, first->name);
	(*combo)->starting = first;
	(*combo)->paths_num = search_for_path(first, *combo, (*combo)->paths_num,
											farm->vertex_num);
	clear_bfs_marks(farm->vertexes, 0);
	compute_distances(farm, (*combo)->name, 0);
	sort_links(farm->start);
	if (!(*combo)->paths_num)
		return (0);
	return (1);
}

static void			prepare_for_path_search(t_farm *farm, t_path_combo *combo)
{
	clear_bfs_marks(farm->vertexes, 0);
	compute_distances(farm, combo->name, 0);
	sort_links(farm->start);
}

void				find_combo_with_vertex(t_path_combo **combo,
											t_vertex *first, t_farm *farm)
{
	t_list			*links;
	t_vertex		*vertex;
	int				new_flag;

	if (!prepare_for_combo_search(combo, first, farm))
		return ;
	new_flag = 0;
	links = farm->start->links;
	vertex = *(t_vertex **)links->content;
	calculate_combo(*combo, farm->ants_num);
	while (vertex && vertex->dist >= 0 && !vertex->is_end &&
			(vertex->real_dist + 1 < (*combo)->lines_num))
	{
		if (vertex != first && !ft_strequ(vertex->path_name, (*combo)->name))
			new_flag = search_for_path(vertex, *combo, (*combo)->paths_num,
										farm->vertex_num);
		(*combo)->paths_num += new_flag;
		prepare_for_path_search(farm, *combo);
		links = farm->start->links;
		vertex = *(t_vertex **)links->content;
		if (ft_strequ(vertex->name, (*combo)->name))
			vertex = *(t_vertex **)links->next->content;
		calculate_combo(*combo, farm->ants_num);
	}
}

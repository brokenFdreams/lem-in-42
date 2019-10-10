/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_find_vertex_combo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:34:55 by anna              #+#    #+#             */
/*   Updated: 2019/10/10 16:49:07 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				prepare_for_combo_search(t_path_combo **combo,
											t_vertex *first, t_farm *farm,
											int best_one_flag)
{
	if (!*combo)
		*combo = init_path_combo();
	else
		clear_combo(combo, 0);
	ft_strcpy((*combo)->name, first->name);
	(*combo)->starting = first;
	(*combo)->is_best_one = best_one_flag;
	(*combo)->paths_num = search_for_path(first, *combo, (*combo)->paths_num, farm->vertex_num);
	clear_bfs_marks(farm->vertexes, 0);
	compute_distances(farm, (*combo)->name, 0);
	sort_links(farm->start);
}

void				find_combo_with_vertex(t_path_combo **combo,
											t_vertex *first, t_farm *farm,
											int best_one_flag)
{
	t_list			*links;
	t_vertex		*vertex;
	int				new_path_flag;

	prepare_for_combo_search(combo, first, farm, best_one_flag);
	if (!(*combo)->paths_num)
		return ;
	new_path_flag = 0;
	links = farm->start->links; //
	vertex = *(t_vertex **)links->content;
	calculate_combo(*combo, farm->ants_num); //
	while (vertex->dist >= 0 && !vertex->is_end) //while (vertex->dist >= 0 && !vertex->is_end && (vertex->real_dist + 1 <= (*combo)->lines_num))
	{
		if (vertex != first && !ft_strequ(vertex->path_name, (*combo)->name))
			new_path_flag = search_for_path(vertex, *combo, (*combo)->paths_num, farm->vertex_num);
		(*combo)->paths_num += new_path_flag;
		clear_bfs_marks(farm->vertexes, 0);
		compute_distances(farm, (*combo)->name, 0);
		sort_links(farm->start);
		links = farm->start->links;
		vertex = *(t_vertex **)links->content;
		if (ft_strequ(vertex->name, (*combo)->name))
			vertex = *(t_vertex **)links->next->content;
		calculate_combo(*combo, farm->ants_num); //
	}
	log_combo(STDOUT_FILENO, *combo, "New combo:\n");
}

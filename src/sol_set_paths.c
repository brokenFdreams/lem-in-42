/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_set_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:35:30 by anna              #+#    #+#             */
/*   Updated: 2019/10/10 16:38:51 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				swap_paths(t_path *more_steps, t_path *less_steps)
{
	int				temp_steps;
	t_vertex		*temp_vertex;

	temp_steps = more_steps->steps;
	more_steps->steps = less_steps->steps;
	less_steps->steps = temp_steps;
	temp_vertex = more_steps->starting_vertex;
	more_steps->starting_vertex = less_steps->starting_vertex;
	less_steps->starting_vertex = temp_vertex;
	more_steps->starting_vertex->path_num = more_steps->num;
	less_steps->starting_vertex->path_num = less_steps->num;
}

void				sort_paths(t_path_combo *combo)
{
	t_path			*temp_a;
	t_path			*temp_b;
	// t_path			*first;

	// first = combo->paths;
	temp_a = combo->paths;
	while (temp_a->next)
	{
		temp_b = temp_a->next;
		while (temp_b)
		{
			if (temp_a->steps > temp_b->steps)
				swap_paths(temp_a, temp_b);
			temp_b = temp_b->next;
		}
		temp_a = temp_a->next;
	}
}

void				set_paths(t_farm *farm)
{
	t_path_combo	*combo;

	combo = NULL;
	find_combo_with_vertex(&combo, farm->combo->starting, farm, 1);
	ft_strcpy(farm->end->path_name, combo->name);
	free_combo(&combo);
	clear_bfs_marks(farm->vertexes, 0);
	restore_dist(farm->vertexes);
	sort_links(farm->start);
	sort_paths(farm->combo);
	farm->start->ants_num = farm->ants_num;
	log_combo(STDOUT_FILENO, farm->combo, "Sorted paths\n");

}
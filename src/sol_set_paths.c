/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_set_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:35:30 by anna              #+#    #+#             */
/*   Updated: 2019/10/17 03:34:42 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			swap_paths(t_path *more_steps, t_path *less_steps)
{
	int				temp_steps;
	t_vertex		*temp_vertex;
	t_vertex		**temp_chain;

	temp_steps = more_steps->steps;
	more_steps->steps = less_steps->steps;
	less_steps->steps = temp_steps;
	temp_vertex = more_steps->starting_vertex;
	more_steps->starting_vertex = less_steps->starting_vertex;
	less_steps->starting_vertex = temp_vertex;
	temp_chain = more_steps->chain;
	more_steps->chain = less_steps->chain;
	less_steps->chain = temp_chain;
	more_steps->starting_vertex->path_num = more_steps->num;
	less_steps->starting_vertex->path_num = less_steps->num;
}

static void			sort_paths(t_path_combo *combo)
{
	int				a;
	int				b;
	// t_path			*first;

	// first = combo->paths;
	a = 0;
	while (a < combo->paths_num)
	{
		b = a + 1;
		while (b < combo->paths_num)
		{
			if (combo->paths[a]->steps > combo->paths[b]->steps)
				swap_paths(combo->paths[a], combo->paths[b]);
			b++;
		}
		a++;
	}
}

void				make_chains(t_farm *farm)
{
	int				p_i;
	int				c_i;
	t_path			**paths;

	p_i = 0;
	paths = farm->combo->paths;
	while (p_i < farm->combo->paths_num)
	{
		c_i = 0;
		while (c_i < (paths[p_i]->steps - 1))
		{
			paths[p_i]->chain[c_i]->next = paths[p_i]->chain[c_i + 1];
			c_i++;
		}
		p_i++;
	}
}

void				set_paths(t_farm *farm)
{
	// t_path_combo	*combo;

	// combo = NULL;
	// find_combo_with_vertex(&combo, farm->combo->starting, farm, 1);
	// if (farm->options->log && farm->log_fd > -1)
		// log_combo(farm->log_fd, combo, "Attaching vertexes to each other, order:\n");
	ft_strcpy(farm->end->path_name, farm->combo->name);
	// free_combo(&combo);
	// clear_bfs_marks(farm->vertexes, 0);
	// restore_dist(farm->vertexes);
	// sort_links(farm->start);
	sort_paths(farm->combo);
	make_chains(farm);
	farm->start->ants_num = farm->ants_num;
	if (farm->options->log && farm->log_fd > -1)
		log_combo(farm->log_fd, farm->combo, "Sorted paths\n");

}
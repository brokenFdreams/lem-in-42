/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_find_combos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:34:44 by anna              #+#    #+#             */
/*   Updated: 2019/10/10 16:44:09 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					compare_combos(t_path_combo *current, t_path_combo *new)
{
	if (!current)
		return (1);
	if (new->paths_num < 1)
		return (0);
	if (new->lines_num < current->lines_num)
		return (1);	
	return (0);	
}

void				copy_combo(t_path_combo **old, t_path_combo *new)
{
	if (*old)
		clear_combo(old, 1);
	else
		*old = init_path_combo();
	(*old)->starting = new->starting;
	(*old)->lines_num = new->lines_num;
	(*old)->num_of_paths_to_use = new->num_of_paths_to_use;
	(*old)->paths_num = new->paths_num;
	(*old)->paths = new->paths;
	ft_strclr((*old)->name);
	ft_strcpy((*old)->name, new->name);
}

void				find_path_combo(t_farm *farm)
{
	t_path_combo	*combo;
	t_path_combo	*best_combo;
	t_list			*start_links;
	t_vertex		*vertex;
	int				i;

	i = 0;
	best_combo = NULL;
	combo = NULL;
	start_links = copy_links(farm->start->links);
	farm->original_links_of_start = start_links;
	while (start_links)
	{
		vertex = *(t_vertex **)start_links->content;
		// if (best_combo && (i >= farm->end->links_num / 2))
		// 	break ;
		find_combo_with_vertex(&combo, vertex, farm, 0);
		if (compare_combos(best_combo, combo))
			copy_combo(&best_combo, combo);
		else
			clear_combo(&combo, 1);
		start_links = start_links->next;
		restore_vertexes(farm);
		i++;
	}
	farm->combo = best_combo;
}

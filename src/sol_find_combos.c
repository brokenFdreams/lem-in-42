/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_find_combos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:34:44 by anna              #+#    #+#             */
/*   Updated: 2019/10/17 13:12:31 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			compare_combos(t_path_combo *current, t_path_combo *new)
{
	if (!current)
		return (1);
	if (new->paths_num < 1)
		return (0);
	if (new->lines_num < current->lines_num)
		return (1);	
	return (0);	
}

void				copy_paths(t_path_combo *dest, t_path_combo *src)
{
	int				p_i;
	// int				c_i;

	p_i = 0;
	while (p_i < src->paths_num)
	{
		dest->paths[p_i]->num = src->paths[p_i]->num;
		dest->paths[p_i]->starting_vertex = src->paths[p_i]->starting_vertex;
		dest->paths[p_i]->steps = src->paths[p_i]->steps;
		ft_memcpy(dest->paths[p_i]->chain, src->paths[p_i]->chain, sizeof(t_vertex *) * src->paths[p_i]->steps);
		p_i++;
	}
}

static void			copy_combo(t_path_combo **old, t_path_combo *new,
								t_farm *farm)
{
	if (*old)
		clear_combo(old, 1);
	else
		*old = init_path_combo(farm);
	(*old)->starting = new->starting;
	(*old)->lines_num = new->lines_num;
	(*old)->num_of_paths_to_use = new->num_of_paths_to_use;
	(*old)->paths_num = new->paths_num;
	copy_paths(*old, new);
	ft_strclr((*old)->name);
	ft_strcpy((*old)->name, new->name);
}

void			make_new_combo_search(t_farm *farm, t_path_combo **best_combo,
							t_path_combo **combo, t_vertex *vertex)
{
	static int	combo_num = 1;
	char		*combo_num_str;
	char		*message;

	find_combo_with_vertex(combo, vertex, farm);
	if (farm->options->stat)
		print_combo_stat(*combo, farm->options->color);
	if (farm->options->log && farm->log_fd > -1)
	{
		combo_num_str = ft_itoa(combo_num);
		message = ft_strjoin("Combo ", combo_num_str);
		log_combo(farm->log_fd, *combo, message);
		ft_strdel(&combo_num_str);
		ft_strdel(&message);
	}
	if (compare_combos(*best_combo, *combo))
		copy_combo(best_combo, *combo, farm);
	else
		clear_combo(combo, 1);
	combo_num++;
}

void				del_combo(t_path_combo **combo)
{
	ft_strdel(&(*combo)->name);
	free(*combo);
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
		if (best_combo && ((best_combo->lines_num <= vertex->real_dist + 1) ||
							(farm->end->links_num / 2 + 1) <= i))
			break ;
		make_new_combo_search(farm, &best_combo, &combo, vertex);
		start_links = start_links->next;
		restore_vertexes(farm);
		i++;
	}
	if (!ft_strequ(combo->name, best_combo->name))
		del_combo(&combo);
	farm->combo = best_combo;
}

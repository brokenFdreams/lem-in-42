/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_calculating_path_combo.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:43:16 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 17:00:43 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				clear_path(t_path *path)
{
	path->starting_vertex = NULL;
	path->num = -1;
	path->steps = -1;
	ft_bzero(path->chain, path->steps * sizeof(t_vertex *));
}

static int			compute_line_num(t_path **paths, int i, int ants_num)
{
	int				total_steps;
	int				j;
	int				lines_num;

	total_steps = paths[i]->steps;
	j = 0;
	while (j < i)
	{
		total_steps += paths[j]->steps;
		j++;
	}
	lines_num = (ants_num + total_steps) / (paths[i]->num + 1) - 1;
	if ((ants_num + total_steps) % (paths[i]->num + 1) > 0)
		lines_num++;
	return (lines_num);
}

void				calculate_combo(t_path_combo *combo, int ants_num)
{
	int				min_num_of_lines;
	int				opt_path_num;
	int				num_of_lines;
	int				i;

	min_num_of_lines = INT_MAX;
	i = 0;
	while (i < combo->paths_num)
	{
		num_of_lines = compute_line_num(combo->paths, i, ants_num);
		if (num_of_lines < min_num_of_lines)
		{
			min_num_of_lines = num_of_lines;
			opt_path_num = i;
		}
		i++;
	}
	combo->num_of_paths_to_use = opt_path_num + 1;
	combo->lines_num = min_num_of_lines;
}

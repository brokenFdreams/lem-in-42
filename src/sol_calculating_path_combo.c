/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_calculating_path_combo.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:43:16 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/12 17:47:02 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


static int			compute_line_num(t_path *first, t_path *last, int ants_num)
{
	int				total_steps;
	t_path			*temp;
	int				lines_num;

	total_steps = last->steps;
	temp = first;
	while (temp && temp != last)
	{
		total_steps += temp->steps;
		temp = temp->next;
	}
	lines_num = (ants_num + total_steps) / (last->num + 1) - 1;
	if ((ants_num + total_steps) % (last->num + 1) > 0)
		lines_num++;
	return (lines_num);
}

void				calculate_combo(t_path_combo *combo, int ants_num)
{
	t_path			*temp;
	int				min_num_of_lines;
	int				opt_path_num;
	int				num_of_lines;

	min_num_of_lines = INT_MAX;
	temp = combo->paths;
	while (temp)
	{
		num_of_lines = compute_line_num(combo->paths, temp, ants_num);
		if (num_of_lines < min_num_of_lines)
		{
			min_num_of_lines = num_of_lines;
			opt_path_num = temp->num + 1;
		}
		temp = temp->next;
	}
	combo->num_of_paths_to_use = opt_path_num;
	combo->lines_num = min_num_of_lines;
}

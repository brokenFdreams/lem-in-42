/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_releasing_ants.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:35:02 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 16:46:58 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		move_ant(t_ant *ant, t_vertex *vertex)
{
	if (!ant->current_vertex->is_start)
		ant->current_vertex->is_occupied = 0;
	else
		ant->current_vertex->ants_num--;
	ant->current_vertex = vertex;
	ant->current_vertex->is_occupied = 1;
	if (ant->current_vertex->is_end)
	{
		ant->current_vertex->is_occupied = 0;
		ant->current_vertex->ants_num++;
	}
}

static t_vertex	*find_vertex_for_ant(t_ant *ant, t_path_combo *combo)
{
	int			path_num;

	path_num = ant->num % combo->num_of_paths_to_use - 1;
	if (path_num < 0)
		path_num = combo->num_of_paths_to_use - 1;
	ant->path_num = path_num;
	if (combo->paths[path_num])
		return (combo->paths[path_num]->starting_vertex);
	return (NULL);
}

/*
** move_status:
**  1 - ant made a move
**  0 - ant couldn't find a move, he is not last in queue nor he is at start
** -1 - ant couldn't find a move and he is at start or last in queue
*/

static int		find_move(t_ant *ant, int ants_num, t_path_combo *combo)
{
	t_vertex	*vertex;

	if (ant->current_vertex->is_start)
	{
		vertex = find_vertex_for_ant(ant, combo);
		if (!vertex || (vertex->is_occupied && !vertex->is_end))
			return (-1);
		move_ant(ant, vertex);
		return (1);
	}
	if (ant->current_vertex->next && ant->current_vertex->next->is_occupied)
	{
		if (ant->current_vertex->is_start || ant->num == ants_num)
			return (-1);
		else
			return (0);
	}
	move_ant(ant, ant->current_vertex->next);
	return (1);
}

static void		print_move(t_ant *ant, int colour_flag)
{
	if (colour_flag)
		switch_to_colour(ant->path_num);
	ft_putstr("L");
	ft_putnbr(ant->num);
	ft_putstr("-");
	ft_putstr(ant->current_vertex->name);
	if (colour_flag)
		switch_to_default();
}

void			release_ants(t_farm *farm)
{
	t_ant		*current_ant;
	char		move_status;

	while (farm->end->ants_num < farm->ants_num)
	{
		current_ant = get_next_ant(farm->ant_queue, NULL);
		move_status = 0;
		while (move_status >= 0 && current_ant)
		{
			move_status = find_move(current_ant, farm->ants_num, farm->combo);
			if (move_status > 0 && current_ant != farm->ant_queue->ant)
				write(STDOUT_FILENO, " ", 1);
			if (move_status > 0)
				print_move(current_ant, farm->options->color);
			current_ant = get_next_ant(farm->ant_queue, current_ant);
		}
		renew_ant_queue(farm);
		write(STDOUT_FILENO, "\n", 1);
		calculate_combo(farm->combo, farm->start->ants_num);
	}
}

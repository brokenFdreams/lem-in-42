/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_option_stat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:32:17 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 16:44:25 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			count_links(t_list *list)
{
	int				result;

	result = 0;
	while (list)
	{
		result++;
		list = list->next;
	}
	return (result);
}

static int			get_maximal_dist(t_list *list)
{
	while (list->next)
		list = list->next;
	return ((*(t_vertex **)list->content)->dist);
}

void				print_stat(t_farm *farm)
{
	ft_putstr("\033[1;37m");
	ft_putstr("Graph stat:\n");
	switch_to_default();
	ft_putstr("Rooms number\tEdges of start\tEdges of end\t\
Min distance\tMax distance");
	if (farm->options->color)
		ft_putstr("\033[0;32m");
	ft_putstr("\n");
	ft_putnbr(farm->vertex_num);
	ft_putstr("\t\t");
	ft_putnbr(count_links(farm->start->links));
	ft_putstr("\t\t");
	ft_putnbr(farm->end->links_num);
	ft_putstr("\t\t");
	ft_putnbr((*(t_vertex **)farm->start->links->content)->dist + 1);
	ft_putstr("\t\t");
	ft_putnbr(get_maximal_dist(farm->start->links));
	if (farm->options->color)
		switch_to_default();
	ft_putstr("\n\n");
}

void				print_combo_stat_header(void)
{
	ft_putstr("First vertex\tReal distance\tLines number\tTotal paths\
\tOptimal paths number\n\n");
}

void				print_combo_stat(t_path_combo *combo, int colour_flag)
{
	static int		colour = 11;

	if (colour_flag)
		switch_to_colour(colour);
	ft_putstr(combo->name);
	ft_putstr("\t\t");
	ft_putnbr(combo->starting->real_dist + 1);
	ft_putstr("\t\t");
	ft_putnbr(combo->lines_num);
	ft_putstr("\t\t");
	ft_putnbr(combo->paths_num);
	ft_putstr("\t\t");
	ft_putnbr(combo->num_of_paths_to_use);
	ft_putstr("\n\n");
	if (colour_flag)
		switch_to_default();
	colour = (colour == 11 ? 12 : 11);
}

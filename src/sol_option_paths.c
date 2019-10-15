/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_option_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:44:23 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/12 17:47:01 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			print_path(t_path *path)
{
	t_vertex		*temp_vertex;

	ft_putnbr(path->num);
	ft_putstr(": ");
	temp_vertex = path->starting_vertex;
	ft_putstr(temp_vertex->name);
	while (temp_vertex)
	{
		temp_vertex = temp_vertex->next;
		if (temp_vertex)
		{
			ft_putstr(" --> ");
			ft_putstr(temp_vertex->name);
		}
	}
	ft_putstr("\n");
}

void				print_paths(t_farm *farm)
{
	int				i;
	int				colour;
	t_path			*temp_path;

	i = 0;
	colour = farm->options->color;
	temp_path = farm->combo->paths;
	while (temp_path && (i < farm->combo->num_of_paths_to_use))
	{
		if (colour)
			switch_to_colour(i);
		print_path(temp_path);
		if (colour)
			switch_to_default();
		temp_path = temp_path->next;
		i++;
	}
	ft_putstr("\n");
}

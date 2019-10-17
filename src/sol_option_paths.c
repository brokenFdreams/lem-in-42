/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_option_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:44:23 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/17 02:45:47 by anna             ###   ########.fr       */
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

	i = 0;
	colour = farm->options->color;
	while (farm->combo->paths[i] && (i < farm->combo->num_of_paths_to_use))
	{
		if (colour)
			switch_to_colour(i);
		print_path(farm->combo->paths[i]);
		if (colour)
			switch_to_default();
		i++;
	}
	ft_putstr("\n");
}

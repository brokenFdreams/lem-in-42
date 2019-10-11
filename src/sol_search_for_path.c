/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_search_for_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:35:24 by anna              #+#    #+#             */
/*   Updated: 2019/10/11 16:18:30 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// TODO: check vertex != current_vertex?
t_vertex		*choose_next_vertex(t_list *links, t_path_combo *combo,
									t_vertex *previous, int name_flag)
{
	t_list		*temp;
	t_vertex	*vertex;

	temp = links;
	while (temp)
	{
		vertex = *(t_vertex **)temp->content;
		if (!ft_strequ(vertex->path_name, combo->name)
			&& previous != vertex && !vertex->is_start)
		{
			if (name_flag && !vertex->is_end)
			{
				ft_strclr(vertex->path_name);
				ft_strcpy(vertex->path_name, combo->name);
			}
			return (vertex);
		}
		temp = temp->next;
	}
	return (NULL);
}

static void			mark_path(t_vertex *first, t_path_combo *combo, int num)
{
		t_list		*links;
		t_vertex	*vertex;
		t_vertex	*new;
		t_vertex	*previous;

		vertex = first;
		previous = first;
		ft_strclr(vertex->path_name);
		ft_strcpy(vertex->path_name, combo->name);
		while (!vertex->is_end)
		{
			links = vertex->links;
			vertex->path_num = num;
			new = choose_next_vertex(links, combo, previous, 1);
			previous = vertex;
			if (combo->is_best_one)
				vertex->next = new;
			vertex = new;
		}
}

static void		add_path(t_path_combo *combo, t_vertex *first, int steps)
{
	t_path		*new;
	t_path		*temp;

	new = (t_path *)malloc(sizeof(t_path));
	if (!new)
		ft_error("Memory allocation error\n");
	new->starting_vertex = first;
	new->steps = steps;
	new->next = NULL;
	new->num = combo->paths_num;
	if (combo->paths)
	{
		temp = combo->paths;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else
		combo->paths = new;
}

int				search_for_path(t_vertex *first, t_path_combo *combo,
								int path_num, int vertex_num)
{
	t_list		*links;
	t_vertex	*previous;
	t_vertex	*new;
	t_vertex	*vertex;
	int			steps;

	steps = 1;
	vertex = first;
	previous = first;
	while (steps < vertex_num)
	{
		if (vertex->is_end)
		{
			mark_path(first, combo, path_num);
			add_path(combo, first, steps);
			return (1);
		}
		links = vertex->links;
		if (!(new = choose_next_vertex(links, combo, previous, 0)))
			return (0);
		steps++;
		previous = vertex;
		vertex = new;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_search_for_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:35:24 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 16:50:46 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

static void		mark_path(t_path *path, t_vertex *first,
								t_path_combo *combo, int num)
{
	t_list		*links;
	t_vertex	*vertex;
	t_vertex	*new;
	t_vertex	*previous;
	int			i;

	i = 0;
	vertex = first;
	previous = first;
	ft_strclr(vertex->path_name);
	ft_strcpy(vertex->path_name, combo->name);
	while (!vertex->is_end)
	{
		path->chain[i] = vertex;
		links = vertex->links;
		vertex->path_num = num;
		new = choose_next_vertex(links, combo, previous, 1);
		previous = vertex;
		vertex = new;
		i++;
	}
	path->chain[i] = vertex;
}

static t_path	*add_path(t_path_combo *combo, t_vertex *first, int steps)
{
	combo->paths[combo->paths_num]->num = combo->paths_num;
	combo->paths[combo->paths_num]->starting_vertex = first;
	combo->paths[combo->paths_num]->steps = steps;
	return (combo->paths[combo->paths_num]);
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
			mark_path(add_path(combo, first, steps), first, combo, path_num);
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

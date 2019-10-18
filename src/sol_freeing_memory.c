/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_freeing_memory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 01:00:48 by anna              #+#    #+#             */
/*   Updated: 2019/10/17 18:06:20 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			free_paths(t_path **paths, int paths_num)
{
	int				i;

	i = 0;
	while (i < paths_num)
	{
		ft_memdel((void **)&paths[i]->chain);
		ft_memdel((void **)&paths[i]);
		i++;
	}
}

void				free_combo(t_path_combo **combo, int paths_num)
{
	ft_strdel(&(*combo)->name);
	free_paths((*combo)->paths, paths_num);
	ft_memdel((void **)&(*combo)->paths);
	clear_combo(combo, 1);
	ft_memdel((void **)combo);
}

static void			free_vertexes(t_farm *farm)
{
	int				i;

	i = 0;
	while (farm->vertexes[i])
	{
		ft_lstdel(&farm->vertexes[i]->links, del_content);
		ft_strdel(&farm->vertexes[i]->name);
		ft_strdel(&farm->vertexes[i]->path_name);
		ft_memdel((void **)&farm->vertexes[i]);
		i++;
	}
	ft_memdel((void **)&farm->vertexes);
}

void				free_memory(t_farm *farm)
{
	if (farm->combo)
		free_combo(&farm->combo, farm->end->links_num);
	if (farm->options)
		ft_memdel((void **)&farm->options);
	if (farm->original_links_of_start)
		ft_lstdel(&farm->original_links_of_start, del_content);
	if (farm->vertexes)
		free_vertexes(farm);
	ft_memdel((void **)&farm);
}

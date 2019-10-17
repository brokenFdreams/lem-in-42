/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_freeing_memory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 01:00:48 by anna              #+#    #+#             */
/*   Updated: 2019/10/16 23:16:30 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				free_paths(t_path **paths, int paths_num)
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

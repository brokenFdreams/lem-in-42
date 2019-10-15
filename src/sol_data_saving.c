/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_data_saving.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 22:17:52 by anna              #+#    #+#             */
/*   Updated: 2019/10/15 16:16:27 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path_combo		*init_path_combo(int name_len)
{
	t_path_combo	*new;

	new = (t_path_combo *)malloc(sizeof(t_path_combo));
	if (!new)
		ft_error("Memory allocation error\n");
	new->starting = NULL;
	new->lines_num = 0;
	new->num_of_paths_to_use = 0;
	new->paths_num = 0;
	new->paths = NULL;
	new->name = ft_strnew(name_len);
	new->is_best_one = 0;
	return (new);
}

static int		count_vertexes(t_vertex **vertexes)
{
	t_vertex	**temp;

	temp = vertexes;
	while (*temp)
		temp++;
	return (temp - vertexes);
}

t_farm			*init_farm(t_vertex **vertexes, t_ant_queue *ant_queue,
							int ants_num, t_options *options)
{
	t_farm		*farm;

	farm = (t_farm *)malloc(sizeof(t_farm));
	if (!farm)
		ft_error("Memory allocation error\n");
	farm->start = vertexes[1];
	farm->end = vertexes[0];
	farm->vertexes = vertexes;
	farm->vertex_num = count_vertexes(vertexes);
	farm->ants_num = ants_num;
	farm->ant_queue = ant_queue;
	farm->combo = NULL;
	farm->options = options;
	farm->map_data = NULL;
	return (farm);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:36:41 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 16:16:05 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			create_map_file(t_map_data *map_data)
{
	time_t		rawtime;
	struct tm	*timeinfo;
	char		*map_string;
	char		*temp_map;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	temp_map = create_time_string(timeinfo);
	map_string = ft_strjoin("map_", temp_map);
	ft_strdel(&temp_map);
	map_data->map_fd = open(map_string, O_WRONLY | O_APPEND | O_CREAT, 0644);
	ft_strdel(&map_string);
}

void			save_map_to_file(t_map_data *map_data)
{
	create_map_file(map_data);
	if (map_data->map_fd > -1)
		print_map(map_data->map_fd, map_data->data);
}

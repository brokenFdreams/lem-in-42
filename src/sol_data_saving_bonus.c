/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_data_saving_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:22:24 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 16:33:08 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_options			*init_options(void)
{
	t_options		*new;

	new = (t_options *)malloc(sizeof(t_options));
	if (!new)
		ft_error("Memory allocation error\n");
	new->color = 0;
	new->help = 0;
	new->log = 0;
	new->path = 0;
	new->stat = 0;
	new->quiet = 0;
	new->save_map = 0;
	new->usage = 0;
	return (new);
}

t_map_data			*init_map_data(void)
{
	t_map_data		*new;

	new = (t_map_data *)malloc(sizeof(t_map_data));
	if (!new)
		ft_error("Memory allocation error\n");
	new->ants_num = 0;
	new->end_line = NULL;
	new->start_line = NULL;
	new->rooms_num = 0;
	new->ways_num = 0;
	new->name_len = 0;
	new->room_lines = NULL;
	new->ways = NULL;
	new->data = NULL;
	new->first_room = NULL;
	new->first_way = NULL;
	new->map_fd = -1;
	return (new);
}

void				init_log(t_farm *farm)
{
	time_t			rawtime;
	struct tm		*timeinfo;
	char			*time_string;
	char			*temp_time;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	temp_time = create_time_string(timeinfo);
	time_string = ft_strjoin("log_", temp_time);
	ft_strdel(&temp_time);
	farm->log_fd = open(time_string, O_WRONLY | O_APPEND | O_CREAT, 0644);
	ft_strdel(&time_string);
	if (farm->log_fd < 0)
		ft_putstr("Log file creation error.\n");
}

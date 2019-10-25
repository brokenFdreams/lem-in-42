/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_line_checking.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:33:08 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 17:35:09 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			is_digits_and_space(char **line)
{
	while (*line && **line && ft_isspace(**line))
		(*line)--;
	if (ft_isdigit(**line))
	{
		while (*line && **line && ft_isdigit(**line))
			(*line)--;
		return (1);
	}
	else
		return (0);
}

int			is_coordinates(char **line)
{
	char	*o_line;
	int		digit_flag;

	o_line = *line;
	while (**line)
		(*line)++;
	(*line)--;
	digit_flag = 0;
	digit_flag += is_digits_and_space(line);
	digit_flag += is_digits_and_space(line);
	if (digit_flag < 2)
		return (0);
	else if (*line <= o_line)
		return (0);
	return (1);
}

int			is_comment_or_command(char *line)
{
	return (*line == '#');
}

void		save_start_room(t_list *start_list, t_list *room_list,
								t_map_data *map_data)
{
	char	*line;

	if (!room_list)
		exit_with_map_format("Error: no start room found");
	line = (char *)room_list->content;
	if (map_data->start_line)
		exit_with_map_format("Error: there may be only 1 start room");
	if (!isroom(line))
		exit_with_map_format("Error: incorrect start room");
	map_data->start_line = line;
	(void)start_list;
}

void		save_end_room(t_list *end_list, t_list *room_list,
							t_map_data *map_data)
{
	char	*line;

	if (!room_list)
		exit_with_map_format("Error: no end room found");
	line = (char *)room_list->content;
	if (map_data->end_line)
		exit_with_map_format("Error: there may be only 1 end room");
	if (!isroom(line))
		exit_with_map_format("Error: incorrect end room");
	map_data->end_line = line;
	(void)end_list;
}

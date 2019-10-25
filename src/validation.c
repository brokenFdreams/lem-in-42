/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:44:07 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/24 13:43:43 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				room_validation(char *line, t_map_data *map_data)
{
	if (*line == '#')
		return (1);
	if (*line == 'L')
		exit_with_map_format("A room\'s name may not start with \'L\'");
	if (!isroom(line))
		return (0);
	map_data->rooms_num++;
	return (1);
}

void			validate_room(t_list *data, t_map_data *map_data)
{
	char		*line;

	line = (char *)data->content;
	if (ft_strequ(line, "##start"))
		save_start_room(data, data->next, map_data);
	else if (ft_strequ(line, "##end"))
		save_end_room(data, data->next, map_data);
	else if (!is_comment_or_command(line) &&
		!room_validation(line, map_data))
		exit_with_map_format("Error: invalid room line found");
	if (!map_data->first_room)
		map_data->first_room = data;
}

int				validate_way(t_list *data, t_map_data *map_data)
{
	char		*line;

	line = (char *)data->content;
	if (ft_strequ(line, "##start"))
		exit_with_map_format("Error: ##start command between the ways found");
	else if (ft_strequ(line, "##end"))
		exit_with_map_format("Error: ##end command between the ways found");
	if (*line == '#')
		return (1);
	if (!isway(line))
		exit_with_map_format("Error: incorrect way line found");
	if (!map_data->first_way)
		map_data->first_way = data;
	map_data->ways_num++;
	return (1);
}

void			check_map_read(t_map_data *map_data)
{
	if (!map_data->start_line || !map_data->end_line)
		exit_with_map_format("Error: there must be start and end rooms");
	if (map_data->ways_num < 1)
		exit_with_map_format("Error: no ways found");
}

/*
** Tries to find ants num.
**
** Then goes thru lines, doing some walidations and incrementing rooms_num or
** ways_num if valid room or way found.
** If stumbels upon ##start or ##end commands checks that there is room ahead
** and saves as start or end to map_data.
**
** Finally, checks there is at least two rooms and one way.
*/

void			validation(t_map_data *map_data)
{
	t_list		*temp;
	int			way_flag;

	way_flag = 0;
	temp = map_data->data;
	while (temp && temp->content && *(char *)temp->content == '#' &&
			!ft_strequ((char *)temp->content, "##start") &&
			!ft_strequ((char *)temp->content, "##end"))
		temp = temp->next;
	if (!temp || !(map_data->ants_num = read_num((char *)temp->content)))
		exit_with_map_format("Error: No ants");
	temp = temp->next;
	while (temp && temp->content)
	{
		if (!way_flag && isway((char *)temp->content))
			way_flag = 1;
		if (!way_flag)
			validate_room(temp, map_data);
		else
			validate_way(temp, map_data);
		temp = temp->next;
	}
	check_map_read(map_data);
}

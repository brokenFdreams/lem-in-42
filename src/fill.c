/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 11:58:30 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/24 13:29:59 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Check str, room is it or not
*/

int			isroom(char *str)
{
	if (!*str || *str == 'L' || *str == '#')
		return (0);
	if (!is_coordinates(&str))
		return (0);
	if (!*str)
		return (0);
	str++;
	while (*str && *str != ' ')
		if (!ft_isdigit(*str))
			return (0);
		else
			str++;
	if (!*str)
		return (0);
	str++;
	if (!*str)
		return (0);
	while (*str)
		if (!ft_isdigit(*str))
			return (0);
		else
			str++;
	return (1);
}

/*
** Check str, way is it or not
*/

int			isway(char *str)
{
	if (*str == 'L' || *str == '#')
		return (0);
	while (*str && *str != '-')
		str++;
	if (*str == '\0')
		return (0);
	str++;
	if (*str == '\0')
		return (0);
	return (1);
}

/*
** Fill rooms
*/

void		fill_rooms(t_map_data *map_data)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = map_data->first_room;
	map_data->room_lines = (char**)ft_memalloc(sizeof(char*) *
							(map_data->rooms_num + 1));
	if (!map_data->room_lines)
		ft_error("Memory allocation error\n");
	while (temp && temp != map_data->first_way && i < map_data->rooms_num)
	{
		if (*(char *)temp->content != '#')
		{
			map_data->room_lines[i] = (char *)temp->content;
			i++;
		}
		if (ft_strequ((char *)temp->content, "##start") ||
			ft_strequ((char *)temp->content, "##end"))
			temp = temp->next;
		if (temp)
			temp = temp->next;
	}
}

void		fill_ways(t_map_data *map_data)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = map_data->first_way;
	map_data->ways = (char**)ft_memalloc(sizeof(char*) *
							(map_data->ways_num + 1));
	if (!map_data->ways)
		ft_error("Memory allocation error\n");
	map_data->ways[map_data->ways_num] = NULL;
	while (temp && i < map_data->ways_num)
	{
		if (*(char *)temp->content != '#')
		{
			map_data->ways[i] = (char *)temp->content;
			i++;
		}
		temp = temp->next;
	}
}

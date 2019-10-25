/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_init_vertex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 01:28:44 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 17:23:03 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char		*read_room_name(char **room_line)
{
	char		*line;
	char		*name;
	int			len;

	line = *room_line;
	is_coordinates(&line);
	len = line - *room_line;
	name = ft_strncpy(ft_strnew(len), *room_line, len);
	name[len] = '\0';
	return (name);
}

t_vertex		*init_vertex(char *room_line, char start_flag, char end_flag,
							int name_len)
{
	t_vertex	*new;

	new = (t_vertex *)malloc(sizeof(t_vertex));
	if (!new)
		ft_error("Memory allocation error\n");
	new->name = read_room_name(&room_line);
	new->is_start = start_flag;
	new->is_end = end_flag;
	new->dist = -1;
	new->is_occupied = start_flag;
	new->is_visited = 0;
	new->is_sorted = 0;
	new->links_num = 0;
	new->links = NULL;
	new->next = NULL;
	new->ants_num = 0;
	new->path_num = -1;
	new->path_name = ft_strnew(name_len);
	new->path_name[0] = 'L';
	new->x = ft_strtol(room_line, &room_line, 10);
	new->y = ft_strtol(room_line, NULL, 10);
	return (new);
}

int				is_dublicate_name(char **rooms, int i)
{
	int			j;
	int			len;
	char		*name;

	j = 0;
	name = rooms[i];
	is_coordinates(&name);
	len = name - rooms[i];
	while (j < i)
	{
		if ((rooms[i][0] == rooms[j][0]) && ft_strnequ(rooms[i], rooms[j], len))
			return (1);
		j++;
	}
	return (0);
}

int				room_check(char **rooms)
{
	int			max_len;
	int			len;
	int			i;

	i = 0;
	max_len = 0;
	while (rooms[i])
	{
		len = ft_strlen(rooms[i]);
		if (len > max_len)
			max_len = len;
		if (ft_strchr(rooms[i], '-'))
			return (-1);
		if ((i > 0) && is_dublicate_name(rooms, i))
			return (-2);
		if (*rooms[i] == 'L')
			return (-3);
		i++;
	}
	return (max_len);
}

t_vertex		**collect_vertexes(t_vertex *start, t_vertex *end,
									t_map_data *map_data)
{
	t_vertex	**vertexes;
	int			i;

	vertexes = (t_vertex **)ft_memalloc(sizeof(t_vertex *) *
										(map_data->rooms_num + 1));
	if (!vertexes)
		ft_error("Memory allocation error\n");
	vertexes[0] = end;
	vertexes[1] = start;
	i = 0;
	while (i < map_data->rooms_num - 2)
	{
		vertexes[i + 2] = init_vertex(map_data->room_lines[i], 0, 0,
							map_data->name_len);
		i++;
	}
	return (vertexes);
}

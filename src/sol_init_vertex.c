/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_init_vertex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 01:28:44 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/04 18:41:04 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "structs.h"

static char		*read_room_name(char **room_line)
{
	char		*name;
	char		*space_pos;

	name = *room_line;
	space_pos = ft_strchr(name, ' ');
	name[space_pos - name] = '\0';
	*room_line = space_pos + 1;
	return (name);
}

t_vertex		*init_vertex(char *room_line, char start_flag, char end_flag)
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
	new->ants_num = 0;
	new->path_num = -1;
	new->path_name = ft_strnew(30); // TODO: change to longest name of start's links
	new->path_name[0] = 'L';
	new->x = ft_strtol(room_line, &room_line, 10);
	new->y = ft_strtol(room_line, NULL, 10);
	return (new);
}

t_vertex		**collect_vertexes(t_vertex *start, t_vertex *end,
									char **rooms_lines, int rooms_num)
{
	t_vertex	**vertexes;
	int			i;

	vertexes = (t_vertex **)malloc(sizeof(t_vertex) * rooms_num + 1);
	if (!vertexes)
		ft_error("Memory allocation error\n");
	vertexes[0] = end;
	vertexes[1] = start;
	vertexes[rooms_num] = NULL;
	i = 0;
	while (i < rooms_num - 2)
	{
		vertexes[i + 2] = init_vertex(rooms_lines[i], 0, 0);
		i++;
	}
	return (vertexes);
}

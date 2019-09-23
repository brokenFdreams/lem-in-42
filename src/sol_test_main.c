/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_test_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:50:16 by dtimeon           #+#    #+#             */
/*   Updated: 2019/09/23 21:14:36 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "structs.h"

t_farm			*init_farm(t_vertex **vertexes, t_queue *ant_queue,
							int ants_num)
{
	t_farm		*farm;

	farm = (t_farm *)malloc(sizeof(t_farm));
	if (!farm)
		ft_error("Memory allocation error");
	farm->start = vertexes[1];
	farm->end = vertexes[0];
	farm->ants_num = ants_num;
	farm->ant_queue = ant_queue;
	return (farm);
}

void				set_distance(t_vertex *vertex, int dist)
{

	if (vertex->dist < 0) //
		vertex->dist = dist;
	else //
		vertex->dist = ft_min(dist, vertex->dist); //
}

void				set_distances_by_dfs(t_vertex *vertex, int dist)
{
	t_list		*temp_link;
	t_vertex	*temp_vertex;

	temp_link = vertex->links;
	while (temp_link)
	{
		temp_vertex = *(t_vertex **)temp_link->content;
		set_distance(temp_vertex, dist + 1);
		temp_link = temp_link->next;
	}
	temp_link = vertex->links;
	vertex->is_visited = 1;
	while (temp_link)
	{
		temp_vertex = *(t_vertex **)temp_link->content;
		if (!temp_vertex->is_visited)
			set_distances_by_dfs(temp_vertex, temp_vertex->dist);
		temp_link = temp_link->next;
	}
}

int				compute_distances(t_farm *farm)
{
	farm->end->dist = 0;
	set_distances_by_dfs(farm->end, 0);
	if (farm->start->dist < 0)
		return (0);
	return (1);
}

//
int			read_rooms_and_links(int fd, char ***rooms, char ***links,
									char **start, char **end)
{
	char		*line;
	int			r_i = 0;
	int			l_i = 0;
	int			start_flag = 0;
	int			end_flag = 0;

	*rooms = (char **)ft_memalloc(sizeof(char *) * 10000);
	*links = (char **)ft_memalloc(sizeof(char *) * 100000);
	
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strchr(line, '-') && !start_flag && !end_flag &&
			!ft_strnequ(line, "##start", 7) && !ft_strnequ(line, "##end", 5))
			(*links)[l_i++] = line;
		else if (!start_flag && !end_flag && !ft_strnequ(line, "##start", 7) &&
				!ft_strnequ(line, "##end", 5))
			(*rooms)[r_i++] = line;
		if (start_flag)
		{
			*start = line;
			start_flag = 0;
		}
		else if (end_flag)
		{
			*end = line;
			end_flag = 0;
		}
		if (ft_strnequ(line, "##start", 7))
			start_flag = 1;
		else if (ft_strnequ(line, "##end", 5))
			end_flag = 1;
	}
	return (r_i + 2);
}

int				main(int ac, char **av)
{
	char		**rooms;
	char		**links;
	int			rooms_num;
	t_farm		*farm;
	t_vertex	*start;
	t_vertex	*end;
	t_vertex	**vertexes;
	t_queue		*ant_queue;

	int			fd;
	int			ants_num;
	char		*line;
	char		*start_line;
	char		*end_line;

//
	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	get_next_line(fd, &line);
	ants_num = ft_strtol(line, NULL, 10);

	rooms_num = read_rooms_and_links(fd, &rooms, &links, &start_line, &end_line);
//

	start = init_vertex(start_line, 1, 0);
	end = init_vertex(end_line, 0, 1);
	vertexes = collect_vertexes(start, end, rooms, rooms_num);
	add_links(vertexes, links);
	ant_queue = create_ant_queue(ants_num);
	farm = init_farm(vertexes, ant_queue, ants_num);
	if (!compute_distances(farm))
		ft_error("No path from end to start found");
	printf("Distance from start to end: %d\n", farm->start->dist);
	return (0);
}
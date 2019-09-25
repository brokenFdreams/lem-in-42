/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_test_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:50:16 by dtimeon           #+#    #+#             */
/*   Updated: 2019/09/25 21:23:21 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "structs.h"

t_farm			*init_farm(t_vertex **vertexes, t_ant_queue *ant_queue,
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



void			prepare_vertexes(t_farm *farm)
{
	log_links(1, farm->start, "Before sorting:\n");
	sort_links(farm->start);
	log_links(1, farm->start, "\nBefore deleting impasses:\n");
	remove_impasses(farm->start);
	log_links(1, farm->start, "\nAfter deleting impasses:\n");
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
	t_ant_queue		*ant_queue;

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
		ft_error("No path from end to start found\n");
	printf("Distance from start to end is %d\n", farm->start->dist);
	prepare_vertexes(farm);
	return (0);
}
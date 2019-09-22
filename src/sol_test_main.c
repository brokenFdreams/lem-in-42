/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_test_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:50:16 by dtimeon           #+#    #+#             */
/*   Updated: 2019/09/23 01:38:03 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "structs.h"

#define ANTS_NUM 4
#define ROOMS_NUM 8
#define START "start 4 0"
#define END "end 4 6"
#define ROOM1 "1 4 2"
#define ROOM2 "2 4 4"
#define ROOM3 "3 2 2"
#define ROOM4 "4 0 4"
#define ROOM5 "5 8 2"
#define ROOM6 "6 8 4"

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

int				set_distance(t_vertex *vertex, int dist)
{
	t_list		*temp_link;
	t_vertex	*temp_vertex;

	if (vertex->dist < 0) //
		vertex->dist = dist;
	else //
		vertex->dist = ft_min(dist, vertex->dist); //
	temp_link = vertex->links;
	while (temp_link)
	{
		temp_vertex = (t_vertex *)temp_link->content;
		if (temp_vertex->dist < 0)
			set_distance(temp_vertex, dist + 1);
		temp_link = temp_link->next;
	}
	return (dist);
}

int				compute_distances(t_farm *farm)
{
	int			i;

	i = set_distance(farm->end, 0);
	if (farm->start->dist < 0)
		return (0);
	return (i);
}

int				main(void)
{
	char		*rooms[] = {ROOM1, ROOM2, ROOM3, ROOM4, ROOM5, ROOM6};
	char		*links[] = { "start-1", "3-4", "2-4", "1-5", "6-5", "end-6", "1-2", "2-end", "3-start", NULL };
	int			rooms_num = 8;
	t_farm		*farm;
	t_vertex	*start;
	t_vertex	*end;
	t_vertex	**vertexes;
	t_queue		*ant_queue;

	start = init_vertex(START, 1, 0);
	end = init_vertex(END, 0, 1);
	vertexes = collect_vertexes(start, end, rooms, rooms_num);
	add_links(vertexes, links);
	ant_queue = create_ant_queue(ANTS_NUM);
	farm = init_farm(vertexes, ant_queue, ANTS_NUM);
	compute_distances(farm);
	return (0);
}
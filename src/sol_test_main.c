/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_test_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:50:16 by dtimeon           #+#    #+#             */
/*   Updated: 2019/09/26 22:35:10 by dtimeon          ###   ########.fr       */
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
		ft_error("Memory allocation error\n");
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
	// log_links(1, farm->start, "Before sorting:\n");
	sort_links(farm->start);
	// log_links(1, farm->start, "\nBefore deleting impasses:\n");
	remove_impasses(farm->start);
	// log_links(1, farm->start, "\nAfter deleting impasses:\n");
}

void			move_ant(t_ant *ant, t_vertex *vertex)
{
	if (!ant->current_vertex->is_start)
		ant->current_vertex->is_occupied = 0;
	ant->current_vertex = vertex;
	ant->current_vertex->is_occupied = 1;
	if (ant->current_vertex->is_end)
	{
		ant->current_vertex->is_occupied = 0;
		ant->current_vertex->ants_num++;
	}
}

int				find_move(t_ant *ant, int ants_num)
{
	t_list		*vertex_list;
	t_vertex	*vertex;

	vertex_list = ant->current_vertex->links;
	while (vertex_list)
	{
		vertex = *(t_vertex **)vertex_list->content;
		if (!vertex->is_occupied &&
			(vertex->dist <= (ant->current_vertex->dist + 1) ||
			(ant->current_vertex->is_start &&
			(ants_num - ant->num) > vertex->dist)))
		{
			move_ant(ant, vertex);
			return (1);
		}
		if (!vertex->is_occupied)
			break ;
		vertex_list = vertex_list->next;
	}
	if (ant->current_vertex->is_start || ant->num == ants_num)
		return (-1);
	return (0);	
}

void			print_move(t_ant *ant)
{
	ft_putstr("L");
	ft_putnbr(ant->num);
	ft_putstr("-");
	ft_putstr(ant->current_vertex->name);
}

void			del_ant_queue_till(t_ant_queue **head, t_ant_queue *to_keep)
{
	t_ant_queue	*temp;
	t_ant		*temp_ant;

	temp = *head;

	while (temp != to_keep)
	{
		*head = temp->next;
		temp_ant = temp->ant;
		ft_memdel((void **)&temp_ant);
		free(temp);
		temp = *head;
	}
}

void			del_ant_queue_node(t_ant_queue **to_del, t_ant_queue *previous)
{
	previous->next = (*to_del)->next;
	ft_memdel((void **)(*to_del)->ant);
	ft_memdel((void **)to_del);
}

void			renew_ant_queue(t_farm *farm)
{
	t_ant_queue	*ant_queue_head;
	t_ant_queue	*temp_ant_queue1;
	t_ant_queue	*temp_ant_queue2;

	ant_queue_head = farm->ant_queue;
	temp_ant_queue1 = ant_queue_head;
	while (temp_ant_queue1 && temp_ant_queue1->ant->current_vertex->is_end)
		temp_ant_queue1 = temp_ant_queue1->next;
	del_ant_queue_till(&ant_queue_head, temp_ant_queue1);
	while (temp_ant_queue1 && temp_ant_queue1->next)
	{
		temp_ant_queue2 = temp_ant_queue1->next;
		if (temp_ant_queue2->ant->current_vertex->is_end)
			del_ant_queue_node(&temp_ant_queue2, temp_ant_queue1);
		temp_ant_queue1 = temp_ant_queue1->next;
	}
	farm->ant_queue = ant_queue_head;
}

void			release_ants(t_farm *farm)
{
	t_ant		*current_ant;
	char		move_status;

	while (farm->end->ants_num < farm->ants_num)
	{
		current_ant = get_next_ant(farm->ant_queue, NULL);
		move_status = 0;
		while (move_status >=0 && current_ant)
		{
			if ((move_status = find_move(current_ant, farm->ants_num)) > 0 &&
				current_ant != farm->ant_queue->ant)
				write(STDOUT_FILENO, " ", 1);
			if (move_status > 0)
				print_move(current_ant);
			current_ant = get_next_ant(farm->ant_queue, current_ant);
		}
		renew_ant_queue(farm);
		write(STDOUT_FILENO, "\n", 1);
	}
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
	ant_queue = create_ant_queue(ants_num, start);
	farm = init_farm(vertexes, ant_queue, ants_num);
	if (!compute_distances(farm))
		ft_error("No path from end to start found\n");
	// printf("Distance from start to end is %d\n", farm->start->dist);
	prepare_vertexes(farm);
	release_ants(farm);
	return (0);
}
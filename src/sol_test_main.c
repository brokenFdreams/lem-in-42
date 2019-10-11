/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_test_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:50:16 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/11 17:05:25 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "struct.h"
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
		if (*line == '#' && *(line + 1) != '#')
			continue ;
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
		write(STDOUT_FILENO, line, ft_strlen(line));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (r_i + 2);
}

void			prepare_vertexes(t_farm *farm)
{
	// log_links(1, farm->start, "Before sorting:\n");
	set_real_dist(farm->vertexes);
	sort_links(farm->start);
	// log_links(1, farm->start, "\nBefore deleting impasses:\n");
	remove_impasses(farm->start);
	// log_links(1, farm->start, "\nAfter deleting impasses:\n");
}

// int				find_move(t_ant *ant, int ants_num, int paths_num, char *combo_name)
// {
// 	t_list		*vertex_list;
// 	t_vertex	*vertex;
// 	int			path_no;

// 	vertex_list = ant->current_vertex->links;
// 	path_no = ant->num % paths_num - 1;
// 	if (path_no < 0)
// 		path_no = paths_num - 1;
// 	while (vertex_list)
// 	{
// 		vertex = *(t_vertex **)vertex_list->content;
// 		if (!vertex->is_occupied &&
// 			(ft_strequ(vertex->path_name, combo_name) &&
// 			(vertex->path_num == path_no || vertex->is_end)))
// 		{
// 			move_ant(ant, vertex);
// 			return (1);
// 		}
// 		vertex_list = vertex_list->next;
// 	}
// 	if (ant->current_vertex->is_start || ant->num == ants_num)
// 		return (-1);
// 	return (0);	
// }

// int				search_for_path_recursive(t_path_combo *combo, t_vertex *vertex,
// 											int path_num, int steps)
// {
// 	t_list		*links;
// 	t_vertex	*new;
// 	int			new_search;

// 	if (vertex->is_end)
// 		return (steps);
// 	links = vertex->links;
// 	ft_strclr(vertex->path_name);
// 	ft_strcpy(vertex->path_name, combo->name);
// 	vertex->path_num = path_num;
// 	while (links)
// 	{
// 		new = *(t_vertex **)links->content;
// 		if (!ft_strequ(new->path_name, combo->name) && !new->is_start)
// 		{
// 			new_search = search_for_path_recursive(combo, new, path_num, steps + 1);
// 			if (new_search)
// 				return (new_search);
// 		}
// 		links = links->next;
// 	}
// 	// ft_strclr(vertex->path_name);
// 	vertex->path_num = -1;
// 	return (0);
// }

// int				search_for_path(t_vertex *first, t_path_combo *combo,
// 								int path_num)
// {
// 	int			steps;

// 	steps = 0;
// 	if (!ft_strequ(first->path_name, combo->name))
// 		steps = search_for_path_recursive(combo, first, path_num, 1);
// 	if (steps)
// 	{
// 		add_path(combo, first, steps);
// 		return (1);
// 	}
// 	else
// 		return (0);
// }

int					compute_line_num(t_path *first, t_path *last, int ants_num)
{
	int				total_steps;
	t_path			*temp;
	int				lines_num;

	total_steps = last->steps;
	temp = first;
	while (temp && temp != last)
	{
		total_steps += temp->steps;
		temp = temp->next;
	}
	lines_num = (ants_num + total_steps) / (last->num + 1) - 1;
	if ((ants_num + total_steps) % (last->num + 1) > 0)
		lines_num++;
	return (lines_num);
}

void				calculate_combo(t_path_combo *combo, int ants_num)
{
	t_path			*temp;
	int				min_num_of_lines;
	int				opt_path_num;
	int				num_of_lines;

	min_num_of_lines = INT_MAX;
	temp = combo->paths;
	while (temp)
	{
		num_of_lines = compute_line_num(combo->paths, temp, ants_num);
		if (num_of_lines < min_num_of_lines)
		{
			min_num_of_lines = num_of_lines;
			opt_path_num = temp->num + 1;
		}
		temp = temp->next;
	}
	combo->num_of_paths_to_use = opt_path_num;
	combo->lines_num = min_num_of_lines;
}

int					main(int ac, char **av)
{
	char			**rooms;
	char			**links;
	int				rooms_num;
	t_farm			*farm;
	t_vertex		*start;
	t_vertex		*end;
	t_vertex		**vertexes;
	t_ant_queue		*ant_queue;

	// int				fd;
	int				ants_num;
	char			*line;
	char			*start_line;
	char			*end_line;

//
	// if (ac != 2)
	// 	return (0);
	// fd = open(av[1], O_RDONLY);
	(void)ac;
	(void)av;
	while (get_next_line(STDIN_FILENO, &line) > 0)
		if (*line != '#')
			break;
	write(STDOUT_FILENO, line, ft_strlen(line));
	write(STDOUT_FILENO, "\n", 1);
	ants_num = ft_strtol(line, NULL, 10);

	rooms_num = read_rooms_and_links(STDIN_FILENO, &rooms, &links, &start_line, &end_line);
	write(STDOUT_FILENO, "\n", 1);
//

	start = init_vertex(start_line, 1, 0);
	end = init_vertex(end_line, 0, 1);
	vertexes = collect_vertexes(start, end, rooms, rooms_num);
	add_links(vertexes, links);
	ant_queue = create_ant_queue(ants_num, start);
	farm = init_farm(vertexes, ant_queue, ants_num);
	if (!compute_distances(farm, "", 1))
		ft_error("No path from end to start found\n");
	// printf("Distance from start to end is %d\n", farm->start->dist);
	prepare_vertexes(farm);
	find_path_combo(farm);
	// log_combo(STDOUT_FILENO, farm->combo, "Best combo:\n");
	set_paths(farm);
	release_ants(farm);
	return (0);
}
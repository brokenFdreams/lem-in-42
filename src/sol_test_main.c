/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_test_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:50:16 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/17 18:58:51 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "structs.h"
//
int			read_rooms_and_links(int fd, t_map_data *map_data, int map_fd)
{
	char		*line;
	int			r_i = 0;
	int			l_i = 0;
	int			start_flag = 0;
	int			end_flag = 0;
	int			b;

	map_data->room_lines = (char **)ft_memalloc(sizeof(char *) * 10000);
	map_data->link_lines = (char **)ft_memalloc(sizeof(char *) * 10000);
	
	while ((b = get_next_line(fd, &line)) > 0)
	{
		if (*line == '#' && *(line + 1) != '#')
		{
			write(map_fd, line, ft_strlen(line));
			write(map_fd, "\n", 1);
			free(line);
			continue ;
		}
		if (ft_strchr(line, '-') && !start_flag && !end_flag &&
			!ft_strnequ(line, "##start", 7) && !ft_strnequ(line, "##end", 5))
			(map_data->link_lines)[l_i++] = line;
		else if (!start_flag && !end_flag && !ft_strnequ(line, "##start", 7) &&
				!ft_strnequ(line, "##end", 5))
			(map_data->room_lines)[r_i++] = line;
		if (start_flag)
		{
			map_data->start_line = line;
			start_flag = 0;
		}
		else if (end_flag)
		{
			map_data->end_line = line;
			end_flag = 0;
		}
		if (ft_strnequ(line, "##start", 7))
			start_flag = 1;
		else if (ft_strnequ(line, "##end", 5))
			end_flag = 1;
		write(STDOUT_FILENO, line, ft_strlen(line));
		write(STDOUT_FILENO, "\n", 1);
		write(map_fd, line, ft_strlen(line));
		write(map_fd, "\n", 1);
		if (*line == '#')
			free(line);
	}
	free(line);
	return (r_i + 2);
}

void			prepare_vertexes(t_farm *farm)
{
	if (farm->options->log && farm->log_fd > 0)
		log_links(farm->log_fd, farm->start, "Before sorting:\n");
	set_real_dist(farm->vertexes);
	sort_links(farm->start);
	if (farm->options->log && farm->log_fd > 0)
		log_links(farm->log_fd, farm->start, "\nBefore deleting impasses:\n");
	remove_impasses(farm->start);
	if (farm->options->log && farm->log_fd > 0)
		log_links(farm->log_fd, farm->start, "\nAfter deleting impasses:\n");
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



int					main(int ac, char **av)
{
	t_farm			*farm;
	t_vertex		*start;
	t_vertex		*end;
	t_vertex		**vertexes;
	t_ant_queue		*ant_queue;
	int				fd;
	int				map_fd;
	time_t			rawtime;
	struct tm		*timeinfo;
	char			*map_string;
	char			*temp_map;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	temp_map = create_time_string(timeinfo);
	map_string = ft_strjoin("map_", temp_map);
	ft_strdel(&temp_map);
	
	int				ants_num;
	char			*line;
	t_map_data		*map_data;
	t_options		*options;

//
	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	map_fd = open(map_string, O_WRONLY | O_APPEND | O_CREAT, 0644);
	ft_strdel(&map_string);
	// fd = STDIN_FILENO;
	// (void)ac;
	// (void)av;
	while (get_next_line(fd, &line) > 0)
		if (*line != '#')
			break;
	write(STDOUT_FILENO, line, ft_strlen(line));
	write(STDOUT_FILENO, "\n", 1);
	write(map_fd, line, ft_strlen(line));
	write(map_fd, "\n", 1);

	ants_num = ft_strtol(line, NULL, 10);
	ft_strdel(&line);

	map_data = init_map_data(ants_num);
	map_data->rooms_num = read_rooms_and_links(fd, map_data, map_fd);
	write(STDOUT_FILENO, "\n", 1);

	options = init_options();
//

	options->path = 1;
	// options->color = 1;
	// options->stat = 1;
	options->log = 1;

	start = init_vertex(map_data->start_line, 1, 0, map_data->name_len);
	end = init_vertex(map_data->end_line, 0, 1, map_data->name_len);
	vertexes = collect_vertexes(start, end, map_data);
	add_links(vertexes, map_data);
	ant_queue = create_ant_queue(map_data->ants_num, start);
	farm = init_farm(vertexes, ant_queue, map_data->ants_num, options);
	farm->map_data = map_data;

	if (farm->options->log)
		init_log(farm);
	if (!compute_distances(farm, "", 1))
		ft_error("No path from end to start found\n");
	prepare_vertexes(farm);
	if (farm->options->stat)
	{
		print_stat(farm);
		print_combo_stat_header();
	}
	find_path_combo(farm);
	if (farm->options->log && farm->log_fd > 0)
		log_combo(farm->log_fd, farm->combo, "Best combo:\n");
	set_paths(farm);
	if (farm->options->path)
		print_paths(farm);
	if (farm->options->log && farm->log_fd > -1)
	{
		close(farm->log_fd);
	}
	write(farm->log_fd, "\nAnts number: ", 14);
	release_ants(farm);
	free_memory(farm);
	
	free(map_data->room_lines);
	ft_str_free_array(&map_data->link_lines);
	ft_memdel((void **)&map_data);
	return (0);
}

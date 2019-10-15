/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_test_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:50:16 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/15 20:02:04 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "struct.h"
//
int			read_rooms_and_links(int fd, t_map_data *map_data, int map_fd)
{
	char		*line;
	int			r_i = 0;
	int			l_i = 0;
	int			start_flag = 0;
	int			end_flag = 0;

	map_data->room_lines = (char **)ft_memalloc(sizeof(char *) * 10000);
	map_data->link_lines = (char **)ft_memalloc(sizeof(char *) * 100000);
	
	while (get_next_line(fd, &line) > 0)
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

t_options			*init_options()
{
	t_options		*new;

	new = (t_options *)malloc(sizeof(t_options));
	if (!new)
		ft_error("Memory allocation error\n");
	new->color = 0;
	new->help = 0;
	new->log = 0;
	new->path = 0;
	new->stat = 0;

	return (new);
}

int					count_links(t_list *list)
{
	int				result;

	result = 0;
	while (list)
	{
		result++;
		list = list->next;
	}
	return (result);
}

int					get_maximal_dist(t_list *list)
{
	while (list->next)
		list = list->next;
	return ((*(t_vertex **)list->content)->dist);
}

void				print_stat(t_farm *farm)
{
	ft_putstr("\033[1;37m");
	ft_putstr("Graph stat:\n");
	switch_to_default();
	ft_putstr("Rooms number\tEdges of start\tEdges of end\t\
Min distance\tMax distance");
	if (farm->options->color)
		ft_putstr("\033[0;32m");
	ft_putstr("\n");
	ft_putnbr(farm->vertex_num);
	ft_putstr("\t\t");
	ft_putnbr(count_links(farm->start->links));
	ft_putstr("\t\t");
	ft_putnbr(farm->end->links_num);
	ft_putstr("\t\t");
	ft_putnbr((*(t_vertex **)farm->start->links->content)->dist + 1);
	ft_putstr("\t\t");
	ft_putnbr(get_maximal_dist(farm->start->links));
	if (farm->options->color)
		switch_to_default();
	ft_putstr("\n\n");
}

void				print_combo_stat_header(void)
{
	ft_putstr("First vertex\tReal distance\tLines number\tTotal paths\
\tOptimal paths number\n\n");
}

void				print_combo_stat(t_path_combo *combo, int colour_flag)
{
	static int		colour = 11;

	if (colour_flag)
		switch_to_colour(colour);
	ft_putstr(combo->name);
	ft_putstr("\t\t");
	ft_putnbr(combo->starting->real_dist + 1);
	ft_putstr("\t\t");
	ft_putnbr(combo->lines_num);
	ft_putstr("\t\t");
	ft_putnbr(combo->paths_num);
	ft_putstr("\t\t");
	ft_putnbr(combo->num_of_paths_to_use);
	ft_putstr("\n\n");
	if (colour_flag)
		switch_to_default();
	colour = (colour == 11 ? 12 : 11);
}

char			*convert_with_nessesery_zero(unsigned char num)
{
	char		*temp;
	char		*result;

	temp = ft_itoa(num);
	if (num < 10)
	{
		result = ft_strnew(3);
		result[0] = '0';
		result[1] = *temp;
		ft_strdel(&temp);
	}
	else
		result = temp;
	return (result);
}

void		ft_str_free_array(char ***array)
{
	char	**a;

	a = *array;
	while (*a)
		ft_strdel(a++);
	free(*array);
	*array = NULL;
}

char						*ft_join_str_array(char **array)
{
	size_t					len;
	char					*result;
	int						i;

	len = 0;
	i = 0;
	while (array[i])
		len += ft_strlen(array[i++]);
	if (!(result = ft_strnew(len + 1)))
		exit(EXIT_FAILURE);
	i = 0;
	while (*array)
	{
		ft_strcpy(result + i, *array);
		i += ft_strlen(*array);
		array++;
	}
	return (result);
}

char						*ft_join_strings(int str_num, ...)
{
	va_list					ap;
	char					*result;
	char					**args;
	int						i;

	va_start(ap, str_num);
	args = (char **)malloc(sizeof(char *) * (str_num + 1));
	if (!args)
		ft_error("Memory allocation error");
	args[str_num] = NULL;
	i = 0;
	while (i < str_num)
		if (!(args[i++] = ft_strdup(va_arg(ap, char *))))
			return (NULL);
	va_end(ap);
	result = ft_join_str_array(args);
	ft_str_free_array(&args);
	return (result);
}

char				*create_time_string(struct tm *timeinfo)
{
	t_time			time_strings;
	char			*time_str;

	time_strings.month = convert_with_nessesery_zero(timeinfo->tm_mon + 1);
	time_strings.day = convert_with_nessesery_zero(timeinfo->tm_mday);
	time_strings.hour = convert_with_nessesery_zero(timeinfo->tm_hour);
	time_strings.minute = convert_with_nessesery_zero(timeinfo->tm_min);
	time_strings.second = convert_with_nessesery_zero(timeinfo->tm_sec);

	time_str = ft_join_strings(9, time_strings.day, "_", time_strings.month,
	"_", time_strings.hour, "_", time_strings.minute, "_", time_strings.second);
	ft_strdel(&time_strings.month);
	ft_strdel(&time_strings.day);
	ft_strdel(&time_strings.hour);
	ft_strdel(&time_strings.minute);
	ft_strdel(&time_strings.second);
	return (time_str);
}

void				init_log(t_farm *farm)
{
	time_t			rawtime;
	struct tm		*timeinfo;
	char			*time_string;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	time_string = ft_strjoin("log_", create_time_string(timeinfo));
	farm->log_fd = open(time_string, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (farm->log_fd < 0)
		ft_putstr("Log file creation error.\n");
}


void				free_vertexes(t_farm *farm)
{
	int				i;

	i = 0;
	while (farm->vertexes[i])
	{
		ft_lstdel(&farm->vertexes[i]->links, del_content);
		ft_strdel(&farm->vertexes[i]->name);
		ft_strdel(&farm->vertexes[i]->path_name);
		ft_memdel((void **)&farm->vertexes[i]);
		i++;
	}
	ft_memdel((void **)&farm->vertexes);
}

void				free_memory(t_farm *farm)
{
	if (farm->combo)
		free_combo(&farm->combo);
	if (farm->options)
		ft_memdel((void **)&farm->options);
	if (farm->original_links_of_start)
		ft_lstdel(&farm->original_links_of_start, del_content);
	if (farm->vertexes)
		free_vertexes(farm);
	ft_memdel((void **)&farm);
}

t_map_data			*init_map_data(int ants_num)
{
	t_map_data		*new;

	new = (t_map_data *)malloc(sizeof(t_map_data));
	if (!new)
		ft_error("Memory allocation error\n");
	new->ants_num = ants_num;
	new->end_line = NULL;
	new->start_line = NULL;
	new->rooms_num = 0;
	new->name_len = 0;
	new->room_lines = NULL;
	new->link_lines = NULL;
	return (new);
}

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
	char			*time_string;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	time_string = ft_strjoin("map_", create_time_string(timeinfo));
	
	int				ants_num;
	char			*line;
	t_map_data		*map_data;
	t_options		*options;

//
	// if (ac != 2)
	// 	return (0);
	fd = open(av[1], O_RDONLY);
	map_fd = open(time_string, O_WRONLY | O_APPEND | O_CREAT, 0644);
	// fd = STDIN_FILENO;
	(void)ac;
	(void)av;
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

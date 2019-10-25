/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 12:42:36 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/23 17:23:50 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			read_map(t_map_data *map_data)
{
	read_data(map_data);
	validation(map_data);
	fill_rooms(map_data);
	fill_ways(map_data);
}

t_farm			*save_farm_data(t_map_data *map_data, t_options *options)
{
	t_vertex	*start;
	t_vertex	*end;
	t_vertex	**vertexes;
	t_ant_queue	*ant_queue;
	t_farm		*farm;

	map_data->name_len = room_check(map_data->room_lines);
	if (map_data->name_len <= 0)
		show_room_error(map_data->name_len);
	start = init_vertex(map_data->start_line, 1, 0, map_data->name_len);
	end = init_vertex(map_data->end_line, 0, 1, map_data->name_len);
	vertexes = collect_vertexes(start, end, map_data);
	add_links(vertexes, map_data);
	if (!options->quiet)
		ant_queue = create_ant_queue(map_data->ants_num, start);
	else
		ant_queue = NULL;
	farm = init_farm(vertexes, ant_queue, map_data->ants_num, map_data);
	farm->options = options;
	return (farm);
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

void			find_solution(t_farm *farm)
{
	if (!compute_distances(farm, "", 1))
		ft_error("No path from end to start found\n");
	if (!farm->options->quiet)
		print_map(STDOUT_FILENO, farm->map_data->data);
	prepare_vertexes(farm);
	if (farm->options->stat)
	{
		print_stat(farm);
		print_combo_stat_header();
	}
	find_path_combo(farm);
	if (farm->options->log && farm->log_fd > -1)
		log_combo(farm->log_fd, farm->combo, "Best combo:\n");
	set_paths(farm);
	if (farm->options->path)
		print_paths(farm);
	if (farm->options->log && farm->log_fd > -1)
		close(farm->log_fd);
	if (farm->options->quiet)
		print_number_of_lines(farm->combo->lines_num);
	else
		release_ants(farm);
}

int				main(int ac, char **av)
{
	t_options	*options;
	t_map_data	*map_data;
	t_farm		*farm;

	options = init_options();
	if (ac > 1)
		read_options(ac, av, options);
	if (options->help)
		exit_with_help(options->color);
	else if (options->usage)
		exit_with_usage();
	map_data = init_map_data();
	read_map(map_data);
	if (options->save_map)
		save_map_to_file(map_data);
	farm = save_farm_data(map_data, options);
	if (farm->options->log)
		init_log(farm);
	find_solution(farm);
	free_memory(farm);
}

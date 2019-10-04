/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_logging.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:55:58 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/04 21:32:26 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void			log_links(int fd, t_vertex *vertex, char *message)
{
	t_list		*list;
	t_vertex	*temp_vertex;

	(void)message;
	// ft_putstr_fd(message, fd);
	list = vertex->links;
	// ft_putstr_fd("\nVertex with name \"", fd);
	// ft_putstr_fd(vertex->name, fd);
	// ft_putstr_fd("\"", fd);
	while (list)
	{
		temp_vertex = *(t_vertex **)list->content;
		ft_putstr_fd(vertex->name, fd);
		ft_putstr_fd(": \tlink name: ", fd);
		ft_putstr_fd(temp_vertex->name, fd);
		ft_putstr_fd(", dist: ", fd);
		ft_putnbr_fd(temp_vertex->dist, fd);
		ft_putstr_fd(", links_num: ", fd);
		ft_putnbr_fd(temp_vertex->links_num, fd);
		ft_putstr_fd("\n", fd);
		list = list->next;
	}
	ft_putstr_fd("\n", fd);
}

void			log_finding_move(int fd, t_ant *ant)
{
	ft_putstr_fd("\nAnt ", fd);
	ft_putnbr_fd(ant->num, fd);
	log_links(fd, ant->current_vertex, 
				" is about to choose path. His current vertex:");
}

void			log_combo(int fd, t_path_combo *combo, char *message)
{
	t_path		*path;

	ft_putstr_fd(message, fd);
	ft_putstr_fd("Combo name: ", fd);
	ft_putstr_fd(combo->name, fd);
	ft_putstr_fd(", capacity: ", fd);
	ft_putnbr_fd(combo->capacity, fd);
	ft_putstr_fd(", average path length: ", fd);
	ft_putnbr_fd((int)combo->average_path_len, fd);
	ft_putstr_fd(", number of paths: ", fd);
	ft_putnbr_fd(combo->paths_num, fd);
	ft_putstr_fd("\nPaths:\n", fd);
	path = combo->paths;
	while (path)
	{
		ft_putstr_fd("First vertex name: ", fd);
		ft_putstr_fd(path->starting_vertex->name, fd);
		ft_putstr_fd(", steps: ", fd);
		ft_putnbr_fd(path->steps, fd);
		ft_putstr_fd(", path number: ", fd);
		ft_putnbr_fd(path->num, fd);
		ft_putstr_fd("\n\n", fd);
		path = path->next;
	}
}

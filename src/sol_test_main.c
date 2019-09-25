/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_test_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:50:16 by dtimeon           #+#    #+#             */
/*   Updated: 2019/09/25 20:20:02 by dtimeon          ###   ########.fr       */
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

void	ft_lst_del_content(void *content, size_t size)
{
	ft_bzero(content, size);
	ft_memdel(&content);
}

void			remove_impasses(t_vertex *vertex)
{
	t_list		*list;
	t_list		*temp_list;
	t_vertex	*temp_vertex;

	list = vertex->links;
	while (list && list->next)
	{
		temp_list = list->next;
		temp_vertex = *(t_vertex **)temp_list->content;
		if (temp_vertex->dist < 0)
		{
			ft_lstdel(&temp_list, ft_lst_del_content);
			list->next = NULL;
		}
		if (list->next)
			list = list->next;
	}
}

void			ft_swap(void **a, void **b)
{
	void		*tmp;
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int				compare_vertexes(t_vertex *vertex_a, t_vertex *vertex_b)
{
	if (vertex_a->dist < 0 && vertex_b->dist >= 0)
		return (1);
	else if (vertex_a->dist > vertex_b->dist && vertex_b->dist > 0)
		return (1);
	else if (vertex_a->dist == vertex_b->dist)
	{
		if (vertex_a->links_num > vertex_b->links_num)
			return (1);
		return (0);
	}
	else
		return (0);
}

t_list			*ft_sort_list(t_list *lst, int (*cmp)(t_vertex *, t_vertex *))
{
	t_list		*tmp;
	t_list		*first;
	
	first = lst;
	while (lst->next)
	{
		tmp = lst->next;
		while (tmp)
		{
			if (cmp(*(t_vertex **)lst->content, *(t_vertex **)tmp->content))
				ft_swap(&lst->content, &tmp->content);
			tmp = tmp->next;
		}
		lst = lst->next;
	}
	return (first);
}

void			sort_links(t_vertex *start)
{
	t_queue		*queue;
	t_vertex	*vertex;
	t_vertex	*temp_vertex;
	t_list		*list;
	
	queue = NULL;
	push(&queue, start);
	while ((vertex = pop(&queue)) && !vertex->is_sorted)
	{
		vertex->links = ft_sort_list(vertex->links, compare_vertexes);
		vertex->is_sorted = 1;
		list = vertex->links;
		while (list)
		{
			temp_vertex = *(t_vertex **)list->content;
			temp_vertex->links_num++;
			if (!temp_vertex->is_sorted)
				push(&queue, temp_vertex);
			list = list->next;
		}
	}
}

void			log_links(int fd, t_vertex *vertex, char *message)
{
	t_list		*list;
	t_vertex	*temp_vertex;

	ft_putstr_fd(message, fd);
	list = vertex->links;
	ft_putstr_fd("\nLinks of vertex with name \"", fd);
	ft_putstr_fd(vertex->name, fd);
	ft_putstr_fd("\"", fd);
	while (list)
	{
		temp_vertex = *(t_vertex **)list->content;
		ft_putstr_fd("\nlink name: ", fd);
		ft_putstr_fd(temp_vertex->name, fd);
		ft_putstr_fd(", dist: ", fd);
		ft_putnbr_fd(temp_vertex->dist, fd);
		ft_putstr_fd(", links_num: ", fd);
		ft_putnbr_fd(temp_vertex->links_num, fd);
		list = list->next;
	}
	ft_putstr_fd("\n", fd);
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
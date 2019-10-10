/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sol_test_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:50:16 by dtimeon           #+#    #+#             */
/*   Updated: 2019/10/10 14:32:28 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "structs.h"

static int		count_vertexes(t_vertex **vertexes)
{
	t_vertex	**temp;

	temp = vertexes;
	while (*temp)
		temp++;
	return (temp - vertexes);
}

t_farm			*init_farm(t_vertex **vertexes, t_ant_queue *ant_queue,
							int ants_num)
{
	t_farm		*farm;

	farm = (t_farm *)malloc(sizeof(t_farm));
	if (!farm)
		ft_error("Memory allocation error\n");
	farm->start = vertexes[1];
	farm->end = vertexes[0];
	farm->vertexes = vertexes;
	farm->vertex_num = count_vertexes(vertexes);
	farm->ants_num = ants_num;
	farm->ant_queue = ant_queue;
	farm->combo = NULL;
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

void			set_real_dist(t_vertex **vertexes)
{
	int			i;

	i = 0;
	while (vertexes[i])
	{
		vertexes[i]->real_dist = vertexes[i]->dist;
		i++;
	}
}

void			restore_dist(t_vertex **vertexes)
{
	int			i;

	i = 0;
	while (vertexes[i])
	{
		vertexes[i]->dist = vertexes[i]->real_dist;
		i++;
	}
}

void			clear_bfs_marks(t_vertex **vertexes, int path_name_clear_flag)
{
	int			i;

	i = 0;
	while (vertexes[i])
	{
		vertexes[i]->dist = -1;
		vertexes[i]->is_visited = 0;
		vertexes[i]->is_sorted = 0;
		if (path_name_clear_flag)
		{
			vertexes[i]->path_num = -1;
			ft_strclr(vertexes[i]->path_name);
			ft_strcpy(vertexes[i]->path_name, "L");
		}
		i++;
	}
}

void			prepare_vertexes(t_farm *farm)
{
	// log_links(1, farm->start, "Before sorting:\n");
	set_real_dist(farm->vertexes);
	sort_links(farm->start);
	log_links(1, farm->start, "\nBefore deleting impasses:\n");
	remove_impasses(farm->start);
	log_links(1, farm->start, "\nAfter deleting impasses:\n");
}

void			move_ant(t_ant *ant, t_vertex *vertex)
{
	if (!ant->current_vertex->is_start)
		ant->current_vertex->is_occupied = 0;
	else
		ant->current_vertex->ants_num--;
	ant->current_vertex = vertex;
	ant->current_vertex->is_occupied = 1;
	if (ant->current_vertex->is_end)
	{
		ant->current_vertex->is_occupied = 0;
		ant->current_vertex->ants_num++;
	}
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

t_vertex		*find_vertex_for_ant(t_ant *ant, t_path_combo *combo)
{
	static int	original_nim_of_paths = 0;
	// int			diff;
	int			path_num;
 	t_list		*vertex_list;
	t_vertex	*vertex;

	if (original_nim_of_paths == 0)
		original_nim_of_paths = combo->num_of_paths_to_use;
	path_num = ant->num % combo->num_of_paths_to_use - 1;
	if (path_num < 0)
		path_num = combo->num_of_paths_to_use - 1;
	vertex_list = ant->current_vertex->links;
	while (vertex_list)
	{
		vertex = *(t_vertex **)vertex_list->content;
		if (vertex->path_num == path_num || vertex->is_end)
			return (vertex);
		vertex_list = vertex_list->next;
	}
	return (NULL);
}

/*
** move_status:
**  1 - ant made a move
**  0 - ant couldn't find a move, he is not last in queue nor he is at start
** -1 - ant couldn't find a move and he is at start or last in queue
*/

int				find_move(t_ant *ant, int ants_num, t_path_combo *combo)
{
	t_vertex	*vertex;

	if (ant->current_vertex->is_start)
	{
		vertex = find_vertex_for_ant(ant, combo);
		if (!vertex || (vertex->is_occupied && !vertex->is_end))
			return (-1);
		move_ant(ant, vertex);
		return (1);
	}
	if (ant->current_vertex->next && ant->current_vertex->next->is_occupied)
	{
		if (ant->current_vertex->is_start || ant->num == ants_num)
 			return (-1);
		else
			return (0);
	}
	move_ant(ant, ant->current_vertex->next);
	return (1);
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
	ft_memdel((void **)&(*to_del)->ant);
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
		else
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
			move_status = find_move(current_ant, farm->ants_num, farm->combo);
			if (move_status > 0 && current_ant != farm->ant_queue->ant)
				write(STDOUT_FILENO, " ", 1);
			if (move_status > 0)
				print_move(current_ant);
			current_ant = get_next_ant(farm->ant_queue, current_ant);
		}
		renew_ant_queue(farm);
		write(STDOUT_FILENO, "\n", 1);
		calculate_combo(farm->combo, farm->start->ants_num);
	}
}

t_path_combo		*init_path_combo(void)
{
	t_path_combo	*new;

	new = (t_path_combo *)malloc(sizeof(t_path_combo));
	if (!new)
		ft_error("Memory allocation error\n");
	new->starting = NULL;
	new->lines_num = 0;
	new->num_of_paths_to_use = 0;
	new->paths_num = 0;
	new->paths = NULL;
	new->name = ft_strnew(30);
	new->is_best_one = 0;
	return (new);
}

// TODO: check vertex != current_vertex?
t_vertex		*choose_next_vertex(t_list *links, t_path_combo *combo,
									t_vertex *previous, int name_flag)
{
	t_list		*temp;
	t_vertex	*vertex;

	temp = links;
	while (temp)
	{
		vertex = *(t_vertex **)temp->content;
		if (!ft_strequ(vertex->path_name, combo->name)
			&& previous != vertex && !vertex->is_start)
		{
			if (name_flag && !vertex->is_end)
			{
				ft_strclr(vertex->path_name);
				ft_strcpy(vertex->path_name, combo->name);
			}
			return (vertex);
		}
		temp = temp->next;
	}
	return (NULL);
}

void			mark_path(t_vertex *first, t_path_combo *combo, int num)
{
		t_list		*links;
		t_vertex	*vertex;
		t_vertex	*new;
		t_vertex	*previous;

		vertex = first;
		previous = first;
		ft_strclr(vertex->path_name);
		ft_strcpy(vertex->path_name, combo->name);
		while (!vertex->is_end)
		{
			links = vertex->links;
			vertex->path_num = num;
			new = choose_next_vertex(links, combo, previous, 1);
			previous = vertex;
			if (combo->is_best_one)
				vertex->next = new;
			vertex = new;
		}
}

void			add_path(t_path_combo *combo, t_vertex *first, int steps)
{
	t_path		*new;
	t_path		*temp;

	new = (t_path *)malloc(sizeof(t_path));
	if (!new)
		ft_error("Memory allocation error\n");
	new->starting_vertex = first;
	new->steps = steps;
	new->next = NULL;
	new->num = combo->paths_num;
	if (combo->paths)
	{
		temp = combo->paths;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else
		combo->paths = new;
}

int				search_for_path(t_vertex *first, t_path_combo *combo,
								int path_num, int vertex_num)
{
	t_list		*links;
	t_vertex	*previous;
	t_vertex	*new;
	t_vertex	*vertex;
	int			steps;

	steps = 1;
	vertex = first;
	previous = first;
	while (steps < vertex_num)
	{
		if (vertex->is_end)
		{
			mark_path(first, combo, path_num);
			add_path(combo, first, steps);
			return (1);
		}
		links = vertex->links;
		if (!(new = choose_next_vertex(links, combo, previous, 0)))
			return (0);
		steps++;
		previous = vertex;
		vertex = new;
	}
	return (0);
}

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

void				clear_combo(t_path_combo **combo, int clr_paths_flag)
{
	t_path			*temp_a;
	t_path			*temp_b;

	(*combo)->starting = NULL;
	// (*combo)->capacity = 0;
	// (*combo)->average_path_len = 0;
	(*combo)->paths_num = 0;
	ft_strclr((*combo)->name);
	if (clr_paths_flag)
	{
		temp_a = (*combo)->paths;
		while (temp_a)
		{
			temp_b = temp_a;
			temp_a = temp_a->next;
			ft_memdel((void **)&temp_b);
		}
	}
	else
		(*combo)->paths = NULL;
}

void				prepare_for_combo_search(t_path_combo **combo,
											t_vertex *first, t_farm *farm,
											int best_one_flag)
{
	if (!*combo)
		*combo = init_path_combo();
	else
		clear_combo(combo, 0);
	ft_strcpy((*combo)->name, first->name);
	(*combo)->starting = first;
	(*combo)->is_best_one = best_one_flag;
	(*combo)->paths_num = search_for_path(first, *combo, (*combo)->paths_num, farm->vertex_num);
	clear_bfs_marks(farm->vertexes, 0);
	compute_distances(farm, (*combo)->name, 0);
	sort_links(farm->start);
}

t_list				*copy_links(t_list *links)
{
	t_list			*new;
	t_list			*temp;

	if (!links)
		return (NULL);
	new = ft_lstnew(links->content, sizeof(t_vertex **));
	temp = new;
	while (links->next)
	{	
		links = links->next;
		temp->next = ft_lstnew(links->content, sizeof(t_vertex **));
		temp = temp->next;
		if (!temp)
		{
			ft_lstdel(&new, ft_bzero);
			return (NULL);
		}
	}
	temp->next = NULL;
	return (new);
}

void				find_combo_with_vertex(t_path_combo **combo,
											t_vertex *first, t_farm *farm,
											int best_one_flag)
{
	t_list			*links;
	t_vertex		*vertex;
	int				new_path_flag;

	prepare_for_combo_search(combo, first, farm, best_one_flag);
	if (!(*combo)->paths_num)
		return ;
	new_path_flag = 0;
	links = farm->start->links; //
	vertex = *(t_vertex **)links->content;
	calculate_combo(*combo, farm->ants_num); //
	while (vertex->dist >= 0 && !vertex->is_end) //while (vertex->dist >= 0 && !vertex->is_end && (vertex->real_dist + 1 <= (*combo)->lines_num))
	{
		if (vertex != first && !ft_strequ(vertex->path_name, (*combo)->name))
			new_path_flag = search_for_path(vertex, *combo, (*combo)->paths_num, farm->vertex_num);
		(*combo)->paths_num += new_path_flag;
		clear_bfs_marks(farm->vertexes, 0);
		compute_distances(farm, (*combo)->name, 0);
		sort_links(farm->start);
		links = farm->start->links;
		vertex = *(t_vertex **)links->content;
		if (ft_strequ(vertex->name, (*combo)->name))
			vertex = *(t_vertex **)links->next->content;
		calculate_combo(*combo, farm->ants_num); //
	}
	log_combo(STDOUT_FILENO, *combo, "New combo:\n");
}

int					compare_combos(t_path_combo *current, t_path_combo *new)
{
	if (!current)
		return (1);
	if (new->paths_num < 1)
		return (0);
	if (new->lines_num < current->lines_num)
		return (1);	
	return (0);	
}

void				copy_combo(t_path_combo **old, t_path_combo *new)
{
	if (*old)
		clear_combo(old, 1);
	else
		*old = init_path_combo();
	(*old)->starting = new->starting;
	(*old)->lines_num = new->lines_num;
	(*old)->num_of_paths_to_use = new->num_of_paths_to_use;
	(*old)->paths_num = new->paths_num;
	(*old)->paths = new->paths;
	ft_strclr((*old)->name);
	ft_strcpy((*old)->name, new->name);
}

void				restore_vertexes(t_farm *farm)
{
	ft_lstdel(&farm->start->links, ft_bzero);
	farm->start->links = copy_links(farm->original_links_of_start);
	clear_bfs_marks(farm->vertexes, 1);
	restore_dist(farm->vertexes); // change
	sort_links(farm->start);
}

void				find_path_combo(t_farm *farm)
{
	t_path_combo	*combo;
	t_path_combo	*best_combo;
	t_list			*start_links;
	t_vertex		*vertex;
	int				i;

	i = 0;
	best_combo = NULL;
	combo = NULL;
	start_links = copy_links(farm->start->links);
	farm->original_links_of_start = start_links;
	while (start_links)
	{
		vertex = *(t_vertex **)start_links->content;
		// if (best_combo && (i >= farm->end->links_num / 2))
		// 	break ;
		find_combo_with_vertex(&combo, vertex, farm, 0);
		if (compare_combos(best_combo, combo))
			copy_combo(&best_combo, combo);
		else
			clear_combo(&combo, 1);
		start_links = start_links->next;
		restore_vertexes(farm);
		i++;
	}
	farm->combo = best_combo;
}

void				free_combo(t_path_combo **combo)
{
	clear_combo(combo, 1);
	ft_memdel((void **)combo);
}

void				swap_paths(t_path *more_steps, t_path *less_steps)
{
	int				temp_steps;
	t_vertex		*temp_vertex;

	temp_steps = more_steps->steps;
	more_steps->steps = less_steps->steps;
	less_steps->steps = temp_steps;
	temp_vertex = more_steps->starting_vertex;
	more_steps->starting_vertex = less_steps->starting_vertex;
	less_steps->starting_vertex = temp_vertex;
	more_steps->starting_vertex->path_num = more_steps->num;
	less_steps->starting_vertex->path_num = less_steps->num;
}

void				sort_paths(t_path_combo *combo)
{
	t_path			*temp_a;
	t_path			*temp_b;
	// t_path			*first;

	// first = combo->paths;
	temp_a = combo->paths;
	while (temp_a->next)
	{
		temp_b = temp_a->next;
		while (temp_b)
		{
			if (temp_a->steps > temp_b->steps)
				swap_paths(temp_a, temp_b);
			temp_b = temp_b->next;
		}
		temp_a = temp_a->next;
	}
}

void				set_paths(t_farm *farm)
{
	t_path_combo	*combo;

	combo = NULL;
	find_combo_with_vertex(&combo, farm->combo->starting, farm, 1);
	ft_strcpy(farm->end->path_name, combo->name);
	free_combo(&combo);
	clear_bfs_marks(farm->vertexes, 0);
	restore_dist(farm->vertexes);
	sort_links(farm->start);
	sort_paths(farm->combo);
	farm->start->ants_num = farm->ants_num;
	log_combo(STDOUT_FILENO, farm->combo, "Sorted paths\n");

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

	int				fd;
	int				ants_num;
	char			*line;
	char			*start_line;
	char			*end_line;

//
	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		if (*line != '#')
			break;
	write(STDOUT_FILENO, line, ft_strlen(line));
	write(STDOUT_FILENO, "\n", 1);
	ants_num = ft_strtol(line, NULL, 10);

	rooms_num = read_rooms_and_links(fd, &rooms, &links, &start_line, &end_line);
//
	write(STDOUT_FILENO, "\n", 1);
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
	log_combo(STDOUT_FILENO, farm->combo, "Best combo:\n");
	set_paths(farm);
	release_ants(farm);
	return (0);
}
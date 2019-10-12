/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:02:48 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/12 17:46:59 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "structs.h"
# include <fcntl.h>
# include <limits.h>


# include <stdio.h>

/*
** flag == 1 - start, -1 - end, 0 - just room
*/

typedef struct		s_lst
{
	int				coord_x;
	int				coord_y;
	char			*name;
	int				flag;
	struct t_list	**next;
}					t_lst;

void				read_data(char *argv, char ***data);
int					validation(char **data, char ***rooms, char ***ways);
void				ft_error(char *str);

/*
** fill.c
*/

int					isroom(char *str);
int					isway(char *str);
int					fill_rooms(char **data, char ***rooms, int size);
void				fill_ways(char **data, char ***ways, int size);



void				calculate_combo(t_path_combo *combo, int ants_num);
/* 
** sol_init_vertex.c
*/

t_vertex			*init_vertex(char *room_line, char s_flag, char e_flag);
t_vertex			**collect_vertexes(t_vertex *start, t_vertex *end,
										char **rooms_lines, int rooms_num);

/* 
** sol_create_ant_queue.c
*/

t_ant				*get_next_ant(t_ant_queue *queue, t_ant *previous);
t_ant_queue			*create_ant_queue(int ants_left, t_vertex *start);

/* 
** sol_add_links_to_vertex.c
*/

void				add_links(t_vertex **vertexes, char **links_line);

/* 
** sol_distance_computing.c
*/

int					compute_distances(t_farm *farm, char *name,
										int count_links_flag);

/*
** sol_queue_functions.c
*/

void				push(t_queue **queue, t_vertex *vertex);
t_vertex			*pop(t_queue **queue);

/*
** sol_sorting_links.c
*/

void				sort_links(t_vertex *start);

/*
** sol_logging.c
*/

void				log_links(int fd, t_vertex *vertex, char *message);
void				log_finding_move(int fd, t_ant *ant);
void				log_combo(int fd, t_path_combo *combo, char *message);

/*
** sol_removing_impasses.c
*/

void				remove_impasses(t_vertex *vertex);


/*
** sol_search_for_path.c
*/

int					search_for_path(t_vertex *first, t_path_combo *combo,
									int path_num, int vertex_num);
t_vertex			*choose_next_vertex(t_list *links, t_path_combo *combo,
									t_vertex *previous, int name_flag);

/*
** sol_restoring_data.c
*/

void				set_real_dist(t_vertex **vertexes);
void				restore_dist(t_vertex **vertexes);
void				clear_combo(t_path_combo **combo, int clr_paths_flag);
void				clear_bfs_marks(t_vertex **vertexes, 
									int path_name_clear_flag);
void				restore_vertexes(t_farm *farm);

/*
** sol_links_manipulations.c
*/

void				release_ants(t_farm *farm);

/*
** sol_set_paths.c
*/

t_list				*copy_links(t_list *links);

/*
** sol_freeing_memory.c
*/

void				free_combo(t_path_combo **combo);

/*
** sol_find_vertex_combo.c
*/

void				find_combo_with_vertex(t_path_combo **combo,
											t_vertex *first, t_farm *farm,
											int best_one_flag);

/*
** sol_find_combos.c
*/

void				find_path_combo(t_farm *farm);

/*
** sol_data_saving.c
*/

t_farm				*init_farm(t_vertex **vertexes, t_ant_queue *ant_queue,
							int ants_num, t_options *options);
t_path_combo		*init_path_combo(void);

/*
** sol_ant_queue_management.c
*/

void				renew_ant_queue(t_farm *farm);

/*
** sol_add_links_to_vertex.c
*/

void				add_links(t_vertex **vertexes, char **links_line);

/*
** sol_set_paths.c
*/

void				set_paths(t_farm *farm);

/*
** sol_option_colours.c
*/

void				switch_to_colour(int colour_diff);
void				switch_to_default(void);

/*
** sol_option_colours.c
*/

void				calculate_combo(t_path_combo *combo, int ants_num);

/*
** sol_option_paths.c
*/

void				print_paths(t_farm *farm);

/* 
** additional libft functions
*/

long int			ft_strtol(const char *nptr, char **endptr, int base);

#endif

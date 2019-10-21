/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:02:48 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/21 13:27:54 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "structs.h"
# include <fcntl.h>
# include <limits.h>
# include <time.h>
# include <stdarg.h>

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

void				read_data(char ***data);
t_options			*read_options(int argc, char **argv);
int					validation(char **data, char ***rooms, char ***ways);
void				ft_error(char *str);

t_list				*ft_newlist(char **content, int content_size);

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

t_vertex			*init_vertex(char *room_line, char s_flag, char e_flag,
								int name_len);
t_vertex			**collect_vertexes(t_vertex *start, t_vertex *end,
										t_map_data *map_data);

/* 
** sol_create_ant_queue.c
*/

t_ant				*get_next_ant(t_ant_queue *queue, t_ant *previous);
t_ant_queue			*create_ant_queue(int ants_left, t_vertex *start);

/* 
** sol_add_links_to_vertex.c
*/

void				add_links(t_vertex **vertexes, t_map_data *map_data);

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
void				del_content(void *content, size_t size);

/*
** sol_freeing_memory.c
*/

void				free_combo(t_path_combo **combo, int paths_num);
void				free_memory(t_farm *farm);

/*
** sol_find_vertex_combo.c
*/

void				find_combo_with_vertex(t_path_combo **combo,
											t_vertex *first, t_farm *farm);

/*
** sol_find_combos.c
*/

void				find_path_combo(t_farm *farm);

/*
** sol_data_saving.c
*/

t_farm				*init_farm(t_vertex **vertexes, t_ant_queue *ant_queue,
							int ants_num, t_options *options);
t_path_combo		*init_path_combo(t_farm *farm);

/*
** sol_data_saving_bonus.c
*/

t_options			*init_options();
t_map_data			*init_map_data(int ants_num);
void				init_log(t_farm *farm);

/*
** sol_ant_queue_management.c
*/

void				renew_ant_queue(t_farm *farm);

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
** sol_calculating_path_combo.c
*/

void				calculate_combo(t_path_combo *combo, int ants_num);

/*
** sol_option_paths.c
*/

void				print_paths(t_farm *farm);

void				print_combo_stat_header();
void				print_combo_stat(t_path_combo *combo, int colour_flag);

/*
** sol_option_stat.c
*/

void				print_combo_stat(t_path_combo *combo, int colour_flag);
void				print_combo_stat_header(void);
void				print_stat(t_farm *farm);

/*
** sol_string_manipulations.c
*/

char				*convert_with_nessesery_zero(unsigned char num);
void				ft_str_free_array(char ***array);
char				*ft_join_str_array(char **array);
char				*ft_join_strings(int str_num, ...);
char				*create_time_string(struct tm *timeinfo);

/* 
** additional libft functions
*/

long int			ft_strtol(const char *nptr, char **endptr, int base);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:02:48 by fsinged           #+#    #+#             */
/*   Updated: 2019/10/08 16:23:41 by dtimeon          ###   ########.fr       */
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
** additional libft functions
*/

long int			ft_strtol(const char *nptr, char **endptr, int base);

#endif

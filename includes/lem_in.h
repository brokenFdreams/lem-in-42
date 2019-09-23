/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:02:48 by fsinged           #+#    #+#             */
/*   Updated: 2019/09/23 17:56:06 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "structs.h"
# include <fcntl.h>


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

/* 
** sol_init_vertex.c
*/

t_vertex			*init_vertex(char *room_line, char s_flag, char e_flag);
t_vertex			**collect_vertexes(t_vertex *start, t_vertex *end,
										char **rooms_lines, int rooms_num);

/* 
** sol_create_ant_queue.c
*/

t_queue				*create_ant_queue(int ants_left);

/* 
** sol_add_links_to_vertex.c
*/

void				add_links(t_vertex **vertexes, char **links_line);

/* 
** additional libft functions
*/

void				ft_free_strings_array(char ***array);
int					ft_isspace(int c);
int					ft_chrtoint(char c);
char				*ft_strnchr(const char *str, char c, size_t n);
long int			ft_strtol(const char *nptr, char **endptr, int base);

#endif

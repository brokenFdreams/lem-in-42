/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:02:48 by fsinged           #+#    #+#             */
/*   Updated: 2019/09/23 01:19:59 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
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
** additional libft functions
*/

void				ft_free_strings_array(char ***array);
int					ft_isspace(int c);
int					ft_chrtoint(char c);
char				*ft_strnchr(const char *str, char c, size_t n);
long int			ft_strtol(const char *nptr, char **endptr, int base);

#endif

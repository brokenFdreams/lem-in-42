/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsinged <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:02:48 by fsinged           #+#    #+#             */
/*   Updated: 2019/09/20 12:41:04 by fsinged          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

/*
** flag == 1 - start, -1 - end, 0 - just room
*/

typedef struct		s_list
{
	int				coord_x;
	int				coord_y;
	char			*name;
	int				flag;
	struct t_list	**next;
}

void				read_data(char **argv, char ***data);
int					validation(char **data, char ***rooms, char ***ways);
void				ft_error(char *str);

/*
** fill.c
*/

int					isroom(char *str);
int					isway(char *str);
int					fill_rooms(char **data, char ***rooms, int size);
int					fill_ways(char **data, char ***ways, int size);

#endif

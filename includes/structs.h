/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 15:25:44 by dtimeon           #+#    #+#             */
/*   Updated: 2019/09/22 22:08:58 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _STRUCTS_H_
# define _STRUCTS_H_

# include "libft.h"

typedef struct		s_vertex
{
	char			*name;
	int				dist;
	char			is_occupied;
	t_list			*links;
	int				ants_num;
	char			is_start;
	char			is_end;
	int				x;
	int				y;
	int				capacity;
}					t_vertex;

typedef struct		s_ant
{
	int				num;
	t_vertex		*current_vertex;
}					t_ant;

typedef struct		s_queue
{
	t_ant			*ant;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_farm
{
	int				ants_num;
	t_vertex		*start;
	t_vertex		*end;
	t_vertex		**vertexes; //
	t_queue			*ant_queue;
}					t_farm;

# endif